//
// Created by gerdzio21 on 23.05.2023.
//

#ifndef SHIPS_BATTLESHIP_H
#define SHIPS_BATTLESHIP_H


#include "Ship.h"

class Battleship : public Ship {
public:
    Battleship() : Ship("Battleship", 4) {}
};


#endif //SHIPS_BATTLESHIP_H
