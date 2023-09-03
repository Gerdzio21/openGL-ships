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
    Ship* createShip() override {
        return new AircraftCarrier();
    }
};

class BattleshipFactory : public ShipFactory {
public:
    Ship* createShip() override {
        return new Battleship();
    }
};

class CruiserFactory : public ShipFactory {
public:
    Ship* createShip() override {
        return new Cruiser();
    }
};

class FrigateFactory : public ShipFactory {
public:
    Ship* createShip() override {
        return new Frigate();
    }
};


#endif //SHIPS_SHIPFACTORY_H
