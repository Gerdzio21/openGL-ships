//
// Created by gerdzio21 on 15.08.2023.
//

#ifndef UNTITLED_SHIPVIEWER_H
#define UNTITLED_SHIPVIEWER_H

#include <GL/freeglut.h>
#include "../ShipOrientation.h"

class ShipViewer {

public:
    void drawShip(int col, int row, int shipLength, ShipOrientation orientation);

    void drawShip(int col, int row, int shipLength, ShipOrientation orientation, GLfloat R, GLfloat G, GLfloat B);

    void drawSector(int col, int row, ShipOrientation orientation);

    void drawSector(int col, int row, ShipOrientation orientation, GLfloat R, GLfloat G, GLfloat B);

    void drawShipOutline(int x, int y, int length, ShipOrientation shipOrientation);
};


#endif //UNTITLED_SHIPVIEWER_H
