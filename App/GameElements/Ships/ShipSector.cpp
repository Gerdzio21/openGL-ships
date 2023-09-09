#include "ShipSector.h"

//
// Created by Gerdzio21 on 2023-09-09.
//
ShipSector::ShipSector() {
    health = 100;
}

void ShipSector::damage(int damageValue) {
    if (isDestroyed()) {
        throw AttackException("Sector is already crashed!");
    }
    health -= damageValue;
}

bool ShipSector::isDestroyed() const {
    return health <= 0;
}
