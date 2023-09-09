#include "Ship.h"
#include "ShipFactory.h"

//
// Created by Gerdzio21 on 2023-09-09.
//
Ship *AircraftCarrierFactory::createShip() {
    return new AircraftCarrier();
}

Ship *BattleshipFactory::createShip() {
    return new Battleship();
}

Ship *CruiserFactory::createShip() {
    return new Cruiser();
}

Ship *FrigateFactory::createShip() {
    return new Frigate();
}
