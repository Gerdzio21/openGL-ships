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
#include "GL/freeglut.h"

class Ship {
    const std::string shipType;
    int length;
    std::vector<ShipSector*> shipSectors;
    ShipViewer* shipViewer;
public:
    Ship(std::string shipType, int length);

    void hitSector(int sectorIdx);

    bool isSectorDestroyed(int sectorIdx);

    bool isDestroyed();

    [[nodiscard]] std::string getShipType() const;

    [[nodiscard]] int getLength() const;

public:
    void createSectors();

    void drawShip(int x, int y, ShipOrientation shipOrientation, GLfloat R, GLfloat G, GLfloat B);

    void drawShip(int x, int y, ShipOrientation shipOrientation);

    void drawShipOutline(int x, int y, ShipOrientation shipOrientation);
};


#endif //SHIPS_SHIP_H
