#ifndef __CHARACTER_MODEL_H__
#define __CHARACTER_MODEL_H__

#include "CharacterModelDefinitions.h"
class LevelModel;

struct CellPosition {
    double cellX, cellY;
    CellPosition(double x, double y) {cellX = x; cellY = y;}
};

class CharacterModel {
protected:
    LevelModel* level;
    CharacterType type;
    int hp;
    CharacterStatus status;
    bool alive;
    double cellX;
    double cellY;
public:
    CharacterModel(){};
    CharacterModel(CharacterType);
    virtual void takeDamage(int);
    virtual void setStatus(CharacterStatus);
    virtual bool isAlive();
    virtual void setPosition(double, double);
    virtual CellPosition getPosition();
    virtual double getPositionCellX();
    virtual double getPositionCellY();
    virtual void update(){};
    virtual ~CharacterModel(){};
    double getDistanceToOther(CharacterModel* other);
    virtual void __setLevel(LevelModel*);
};

#endif // !__CHARACTER_MODEL_H__