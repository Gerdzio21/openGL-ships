//
// Created by gerdzio21 on 15.08.2023.
//

#ifndef UNTITLED_SHIPCONTAINERVIEWER_H
#define UNTITLED_SHIPCONTAINERVIEWER_H

#include "GL/freeglut.h"
#include "ShipContainerController.h"

/**
 * @class ShipContainerViewer
 * @brief Viewer for ship container visualization.
 *
 * The `ShipContainerViewer` class is responsible for visualizing the ship container
 * in the game, including drawing ships and the container itself.
 */
class ShipContainerViewer {
public:
    /**
    * @brief Draw the ship container and its ships.
    *
    * @param ships The vector of pointers to ships in the container.
    * @param selectedShipIndex The index of the currently selected ship.
    */
    void drawContainer(std::vector<Ship*> ships, int selectedShipIndex);

    /**
    * @brief Draw a container at a specific position.
    *
    * @param x The x-coordinate of the container's position.
    * @param y The y-coordinate of the container's position.
    */
    void drawOnPosition(int x, int y);
};


#endif //UNTITLED_SHIPCONTAINERVIEWER_H
