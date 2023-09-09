//
// Created by gerdzio21 on 23.05.2023.
//

#ifndef SHIPS_SHIPSECTOR_H
#define SHIPS_SHIPSECTOR_H


#include "AttackException.h"

class ShipSector {
    int health;
public:
    ShipSector();

    void damage(int damageValue);

    [[nodiscard]] bool isDestroyed() const;
};


#endif //SHIPS_SHIPSECTOR_H
