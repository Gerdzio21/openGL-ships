//
// Created by Gerdzio21 on 2023-09-08.
//
#include "ShipContainerController.h"
void ShipContainerController::removeSelectedShipFromContainer() {
    if (selectedShipIndex < 0 || selectedShipIndex >= ships.size()) {
        throw std::out_of_range("Invalid ship index");
    }
    if (selectedShipIndex == ships.size() - 1) {
        ships.erase(ships.begin() + selectedShipIndex);
        selectedShipIndex--; //ujemny index oznacza, że już nie ma statków
    } else {
        ships.erase(ships.begin() + selectedShipIndex);
    }


}

bool ShipContainerController::isEmpty() {
    return ships.empty();
}

void ShipContainerController::selectNextShip() {
    selectedShipIndex = (selectedShipIndex + 1) % ships.size();
}

void ShipContainerController::selectPreviousShip() {
    if (selectedShipIndex == 0) {
        selectedShipIndex = ships.size() - 1;
    } else {
        selectedShipIndex = (selectedShipIndex - 1) % ships.size();
    }
}

int ShipContainerController::getSelectedShipIndex() {
    return selectedShipIndex;
}

std::vector<Ship *> ShipContainerController::getShips() {
    return ships;
}

void ShipContainerController::handleKeyPress(unsigned char key, int x, int y) {
    switch (tolower(key)) {
        case 'w':
            selectNextShip();
            break;
        case 's':
            selectPreviousShip();
            break;
    }
}

void ShipContainerController::emptyContainer() {
    ships.clear();
}

void ShipContainerController::fillContainer() {
    factory = new AircraftCarrierFactory();
    for (int i = 0; i < 1; i++) {
        ships.push_back(factory->createShip());
    }
    factory = new BattleshipFactory();
    for (int i = 0; i < 2; i++) {
        ships.push_back(factory->createShip());
    }
    factory = new CruiserFactory();
    for (int i = 0; i < 2; i++) {
        ships.push_back(factory->createShip());
    }
    factory = new FrigateFactory();
    for (int i = 0; i < 3; i++) {
        ships.push_back(factory->createShip());
    }
}

Ship *ShipContainerController::getSelectedShip() {
    if (selectedShipIndex < 0 || selectedShipIndex >= ships.size()) {
        throw std::out_of_range("Invalid ship index");
    }
    return ships[selectedShipIndex];
}

ShipContainerController::~ShipContainerController() {
    for (Ship* ship: ships) {
        delete ship;
    }
}

ShipContainerController::ShipContainerController() {
    emptyContainer();
    fillContainer();
    selectedShipIndex = 0;
}
