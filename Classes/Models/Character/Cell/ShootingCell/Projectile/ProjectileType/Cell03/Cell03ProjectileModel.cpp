#include "Models/models.h"
#include "Cell03ProjectileModel.h"

/*
Constructor of Cell0ProjectileModel
*/
Cell03ProjectileModel::Cell03ProjectileModel(CharacterModel* source, CharacterModel* target) 
    : ProjectileModel(CELL_03_PROJECTILE, source, target) {
    // Temporary data
    speed = 8.0;
    damage = 1;
}