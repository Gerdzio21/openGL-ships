//
// Created by gerdzio21 on 06.09.2023.
//

#ifndef UNTITLED_SHIPPLACERVIEWER_H
#define UNTITLED_SHIPPLACERVIEWER_H


#include "ShipPlacerController.h"

/**
 * @class ShipPlacerViewer
 * @brief Viewer for ship placement visualization.
 *
 * The `ShipPlacerViewer` class is responsible for visualizing the ship to be placed
 * on the game board based on the current state of the `ShipPlacerController`.
 */
class ShipPlacerViewer {
public:
    /**
     * @brief Draw the ship to be placed on the game board.
     *
     * @param shipPlacerController Pointer to the ShipPlacerController managing ship placement.
     */
    void drawShipToPlace(ShipPlacerController* shipPlacerController) {
        Coordinate hullCoordinate = shipPlacerController->getHullPosition();
        ShipOrientation shipOrientation = shipPlacerController->getShipOrientation();
        if (!shipPlacerController->isPlacerEmpty()) {
            shipPlacerController->getShip()->drawShip(-5 + (hullCoordinate.col - 'A'), -10 + hullCoordinate.row - 1,
                                                      shipOrientation, 0.2123f, 0.0303f, 0.78731233f);
        }
    }
};


#endif //UNTITLED_SHIPPLACERVIEWER_H
