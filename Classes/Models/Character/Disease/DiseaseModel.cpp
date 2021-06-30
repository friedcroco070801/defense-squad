#include "DiseaseModel.h"
using namespace std;

/*
Constructor of DiseaseModel
*/
DiseaseModel::DiseaseModel(DiseaseId id) : CharacterModel(DISEASE), id(id), action(WAITING), dir(LEFT) {
    level = NULL;
    path = NULL;

    // Temporary data
    speed = 0.25f;
    damage = 2;
    hitRechargeTime = 0.5f;
}

/* 
Set level model of disease
*/
void DiseaseModel::__setLevel(LevelModel* level) {
    if (level != NULL) {
        this->level = level;
        path = level->__getEnemyPath();
        currentPath = path->begin();
        nextPath = currentPath + 1;
        changeDirectionOnPath();
    }
}

/* 
Create new instance of DiseaseModel with Factory
*/
DiseaseModel* DiseaseModel::create(DiseaseId id) {
    return new DiseaseModel(id);
}

/*
Change direction of disease on the walking path
*/
void DiseaseModel::changeDirectionOnPath() {
    // End of path
    if (nextPath == path->end()) {
        return;
    }

    // Change direction
    if ((*nextPath)[0] == (*currentPath)[0]) {
        if ((*nextPath)[1] < (*currentPath)[1])
            dir = DOWN;
        else
            dir = UP;
    }
    else if ((*nextPath)[0] < (*currentPath)[0]) {
        dir = LEFT;
    }
    else
        dir = RIGHT;
}

/*
Change direction of disease to the target
*/
void DiseaseModel::changeDirectionToTarget(CellModel* target) {
    auto deltaX = target->getPositionCellX() - cellX;
    auto deltaY = target->getPositionCellY() - cellY;
    if (abs(deltaX) < abs(deltaY)) {
        if (deltaY > 0.0f) dir = UP;
        else dir = DOWN;
    }
    else {
        if (deltaX > 0.0f) dir = RIGHT;
        else dir = LEFT;
    }
}

/*
Destructor of DIseasModel
*/
DiseaseModel::~DiseaseModel() {

}

/*
Update on each updating
*/
void DiseaseModel::update() {
    if (alive && level != NULL) {
        // Search if any cell to attack
        auto cellList = level->__getCellList();
        auto target = cellList.end();
        for (auto it = cellList.begin(); it != cellList.end(); it++) {
            if (getDistanceToOther(*it) <= 1.0f + ACCEPTING_TIME_ERROR) {
                target = it;
                break;
            }
        }

        // If is waiting
        if (action == WAITING) {
            // Detect to attack
            if (target != cellList.end()) {
                action = ATTACKING;
                changeDirectionToTarget(*target);
            }
            else {
                action = WALKING;
                changeDirectionOnPath();
                currentPath++;
                if (nextPath != path->end())
                    nextPath++;
            }
        }

        // If is attacking
        if (action == ATTACKING) {
            // Detect to attack
            if (target != cellList.end()) {
                // Check if recharge time
                auto timePoint = level->getTimeCounter() / hitRechargeTime;
                auto roundTimePoint = round(timePoint);
                auto deltaError = timePoint - roundTimePoint;
                if (deltaError >= -ACCEPTING_TIME_ERROR && deltaError <= ACCEPTING_TIME_ERROR) {
                    hitTarget(*target);
                }
            }
            else {
                action = WALKING;
                changeDirectionOnPath();
                currentPath++;
                if (nextPath != path->end())
                    nextPath++;
            }
        }

        // If is walking
        if (action == WALKING) {
            // Update position
            auto directionVectorX = 0.0f;
            auto directionVectorY = 0.0f;
            if (dir == UP) {directionVectorY = 1.0f;}
            else if (dir == DOWN) {directionVectorY = -1.0f;}
            else if (dir == RIGHT) {directionVectorX = 1.0f;}
            else directionVectorX = -1.0f;
            cellX += directionVectorX * UPDATING_FREQUENCY * speed;
            cellY += directionVectorY * UPDATING_FREQUENCY * speed;

            // Check if the axis is an interger
            auto roundX = round(cellX);
            auto roundY = round(cellY);
            if (abs(cellX - roundX) <= ACCEPTING_TIME_ERROR && abs(cellY - roundY) <= ACCEPTING_TIME_ERROR) {
                action = WAITING;
            }
        }
    }
}

void DiseaseModel::hitTarget(CellModel* target) {
    target->takeDamage(damage);
}