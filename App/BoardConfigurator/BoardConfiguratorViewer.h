//
// Created by gerdzio21 on 06.08.2023.
//

#ifndef UNTITLED_BOARDCONFIGURATORVIEWER_H
#define UNTITLED_BOARDCONFIGURATORVIEWER_H


#include <iostream>
#include "ShipPlacerViewer.h"
#include "../SceneViewer.h"
#include "BoardConfiguratorModel.h"

/**
 * @class BoardConfiguratorViewer
 * @brief Viewer for the board configurator scene.
 *
 * The `BoardConfiguratorViewer` class is responsible for displaying the
 * board configurator scene in the game. It inherits from the `SceneViewer` class.
 */
class BoardConfiguratorViewer : public SceneViewer {

public:
    /**
    * Constructor for the `BoardConfiguratorViewer` class.
    * @param boardConfiguratorModelPtr Pointer to the board configurator model.
    */
    BoardConfiguratorViewer(BoardConfiguratorModel* boardConfiguratorModelPtr);;

    /**
        * Displays the board configurator scene.
        * This function is responsible for rendering the game board, ship container,
        * and currently placed ship if any.
        */
    virtual void displayScene();

private:
    BoardConfiguratorModel* boardConfiguratorModel; ///< Pointer to the board configurator model.
    BoardViewer* boardViewer;
    ShipContainerViewer* shipContainerViewer;
    ShipPlacerViewer* shipPlacerViewer;
};


#endif //UNTITLED_BOARDCONFIGURATORVIEWER_H
