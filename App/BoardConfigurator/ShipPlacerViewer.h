//
// Created by gerdzio21 on 06.09.2023.
//

#ifndef UNTITLED_SHIPPLACERVIEWER_H
#define UNTITLED_SHIPPLACERVIEWER_H


#include "ShipPlacerController.h"

class ShipPlacerViewer {
public:
    void drawShipToPlace(ShipPlacerController* shipPlacerController) {
        Coordinate hullCoordinate = shipPlacerController->getHullPosition();
        ShipOrientation shipOrientation = shipPlacerController->getShipOrientation();
        if (! shipPlacerController->isPlacerEmpty()) {
            shipPlacerController->getShip()->drawShip(-5+(hullCoordinate.col-'A'),-10+hullCoordinate.row-1,shipOrientation,0.2123f,0.0303f, 0.78731233f);
        }
    }
};


#endif //UNTITLED_SHIPPLACERVIEWER_H
