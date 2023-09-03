//
// Created by gerdzio21 on 23.05.2023.
//

#ifndef SHIPS_SHIP_H
#define SHIPS_SHIP_H


#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include "ShipSector.h"
#include "../ShipOrientation.h"
#include "ShipViewer.h"

class Ship {
    const std::string shipType;
    int length;
    std::vector<ShipSector*> shipSectors;
    ShipViewer* shipViewer;
public:
    Ship(std::string shipType, int length) : shipType(std::move(shipType)) {
        this->length = length;
        shipViewer = new ShipViewer();
        createSectors();
    }

    void hitSector(int sectorIdx) {
        if (sectorIdx < 0 || sectorIdx >= length) {
            throw std::out_of_range("Invalid sector index");
        }
        ShipSector* selectedSector = shipSectors[sectorIdx];
        selectedSector->damage(100);
    }

    bool isSectorDestroyed(int sectorIdx) {
        if (sectorIdx < 0 || sectorIdx >= length) {
            throw std::out_of_range("Invalid sector index");
        }
        ShipSector* selectedSector = shipSectors[sectorIdx];
        return selectedSector->isDestroyed();
    }

    bool isDestroyed() {
        bool haveLivingSectors = false;
        for (ShipSector*  sector: shipSectors) {
            if (!sector->isDestroyed()) {
                haveLivingSectors = true;
                break;
            }
        }
        return !haveLivingSectors;
    }

    [[nodiscard]] std::string getShipType() const {
        return shipType;
    }

    [[nodiscard]] int getLength() const {
        return length;
    }

public:
    void createSectors() {
        for (int i = 0; i < length; i++) {
            shipSectors.push_back(new ShipSector());
        }
    }

    void drawShip(int x, int y, ShipOrientation shipOrientation, GLfloat R, GLfloat G, GLfloat B){
        shipViewer -> drawShip(x,y,this->getLength(),shipOrientation,R,G,B);
    }
    void drawShip(int x, int y, ShipOrientation shipOrientation){
        shipViewer -> drawShip(x,y,this->getLength(),shipOrientation);
    }

    void drawShipOutline(int x, int y, ShipOrientation shipOrientation) {
        shipViewer -> drawShipOutline(x,y,this->getLength(),shipOrientation);
    }
};


#endif //SHIPS_SHIP_H
