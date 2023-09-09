#include "Ship.h"

//
// Created by Gerdzio21 on 2023-09-09.
//
Ship::Ship(std::string shipType, int length) : shipType(std::move(shipType)) {
    this->length = length;
    shipViewer = new ShipViewer();
    createSectors();
}

void Ship::hitSector(int sectorIdx) {
    if (sectorIdx < 0 || sectorIdx >= length) {
        throw std::out_of_range("Invalid sector index");
    }
    ShipSector* selectedSector = shipSectors[sectorIdx];
    selectedSector->damage(100);
}

bool Ship::isSectorDestroyed(int sectorIdx) {
    if (sectorIdx < 0 || sectorIdx >= length) {
        throw std::out_of_range("Invalid sector index");
    }
    ShipSector* selectedSector = shipSectors[sectorIdx];
    return selectedSector->isDestroyed();
}

bool Ship::isDestroyed() {
    bool haveLivingSectors = false;
    for (ShipSector* sector: shipSectors) {
        if (!sector->isDestroyed()) {
            haveLivingSectors = true;
            break;
        }
    }
    return !haveLivingSectors;
}

std::string Ship::getShipType() const {
    return shipType;
}

int Ship::getLength() const {
    return length;
}

void Ship::createSectors() {
    for (int i = 0; i < length; i++) {
        shipSectors.push_back(new ShipSector());
    }
}

void Ship::drawShip(int x, int y, ShipOrientation shipOrientation, GLfloat R, GLfloat G, GLfloat B) {
    shipViewer->drawShip(x, y, this->getLength(), shipOrientation, R, G, B);
}

void Ship::drawShip(int x, int y, ShipOrientation shipOrientation) {
    shipViewer->drawShip(x, y, this->getLength(), shipOrientation);
}

void Ship::drawShipOutline(int x, int y, ShipOrientation shipOrientation) {
    shipViewer->drawShipOutline(x, y, this->getLength(), shipOrientation);
}
