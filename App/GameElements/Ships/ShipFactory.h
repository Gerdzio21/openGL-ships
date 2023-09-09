//
// Created by gerdzio21 on 23.05.2023.
//

#ifndef SHIPS_SHIPFACTORY_H
#define SHIPS_SHIPFACTORY_H


#include <memory>
#include "Ship.h"
#include "Battleship.h"
#include "Cruiser.h"
#include "AircraftCarrier.h"
#include "Frigate.h"

class ShipFactory {
public:
    virtual Ship* createShip() = 0;

    virtual ~ShipFactory() = default;
};

class AircraftCarrierFactory : public ShipFactory {
public:
    Ship* createShip() override;
};

class BattleshipFactory : public ShipFactory {
public:
    Ship* createShip() override;
};

class CruiserFactory : public ShipFactory {
public:
    Ship* createShip() override;
};

class FrigateFactory : public ShipFactory {
public:
    Ship* createShip() override;
};


#endif //SHIPS_SHIPFACTORY_H
