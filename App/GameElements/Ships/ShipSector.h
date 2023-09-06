//
// Created by gerdzio21 on 23.05.2023.
//

#ifndef SHIPS_SHIPSECTOR_H
#define SHIPS_SHIPSECTOR_H


#include "AttackException.h"

class ShipSector {
    int health;
public:
    ShipSector() {
        health = 100;
    }

    void damage(int damageValue) {
        if (isDestroyed()) {
            throw AttackException("Sector is already crashed!");
        }
        health -= damageValue;
    }

    [[nodiscard]] bool isDestroyed() const {
        return health <= 0;
    }
};


#endif //SHIPS_SHIPSECTOR_H
