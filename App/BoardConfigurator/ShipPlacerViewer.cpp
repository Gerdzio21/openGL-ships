//
// Created by Gerdzio21 on 2023-09-08.
//
#include "ShipPlacerViewer.h"
void ShipPlacerViewer::drawShipToPlace(ShipPlacerController *shipPlacerController) {
    Coordinate hullCoordinate = shipPlacerController->getHullPosition();
    ShipOrientation shipOrientation = shipPlacerController->getShipOrientation();
    if (!shipPlacerController->isPlacerEmpty()) {
        shipPlacerController->getShip()->drawShip(-5 + (hullCoordinate.col - 'A'), -10 + hullCoordinate.row - 1,
                                                  shipOrientation, 0.2123f, 0.0303f, 0.78731233f);
    }
}
