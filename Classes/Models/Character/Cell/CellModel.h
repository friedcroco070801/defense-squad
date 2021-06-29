#ifndef __CELL_MODEL_H__
#define __CELL_MODEL_H__

#include "../CharacterModel.h"
#include "CellModelDefinitions.h"
#include "../../Level/LevelModel.h"

class CellModel : public CharacterModel {
protected:
    CellId id;
    float distance;
public:
    CellModel(CellId id);
    virtual ~CellModel();

    // Return the distance 
    virtual float getDistance() {return distance;}
    virtual bool canPlantOn(LevelModel level, int cellX, int cellY);
};

#endif // !__CELL_MODEL_H__