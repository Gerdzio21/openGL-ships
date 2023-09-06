//
// Created by gerdzio21 on 06.08.2023.
//

#ifndef UNTITLED_BOARDCONFIGURATORCONTROLLER_H
#define UNTITLED_BOARDCONFIGURATORCONTROLLER_H


#include "BoardConfiguratorModel.h"
#include "BoardConfiguratorViewer.h"
#include "../GameElements/Board.h"
#include "../GameElements/Ships/Ship.h"
#include "../GameElements/ShipOrientation.h"
#include "ShipPlacerController.h"
#include "ShipContainerController.h"
#include "../SceneController.h"

/**
* @class BoardConfiguratorController
* @brief Controller for the board configuration scene.
*
* The `BoardConfiguratorController` class is responsible for handling
* the board configuration scene in the game. It inherits from the
* `SceneController` class.
*/
class BoardConfiguratorController : public SceneController {

public:
    /**
     * Constructor for the `BoardConfiguratorController` class.
     * @param boardConfiguratorModelPtr Pointer to the board configurator model.
     */
    BoardConfiguratorController(BoardConfiguratorModel* boardConfiguratorModelPtr) {
        boardConfiguratorModel = boardConfiguratorModelPtr;
    }

    /**
   * Destructor for the `BoardConfiguratorController` class.
   */
    ~BoardConfiguratorController() {
    }

    /**
       * Handles a key press event.
       * @param key The code of the pressed key.
       * @param x The x-coordinate of the mouse.
       * @param y The y-coordinate of the mouse.
       */
    virtual void handleKeyPress(unsigned char key, int x, int y) {
        if (key == 13) {  //ENTER
            if (boardConfiguratorModel->getState() == State::SelectShip) {
                if (!boardConfiguratorModel->isShipContainerEmpty()) {
                    boardConfiguratorModel->selectShip();
                }
            } else if (boardConfiguratorModel->getState() == State::PlaceShip) {
                boardConfiguratorModel->placeShip();
            }
        } else if (key == 27) {  //ESCAPE
            boardConfiguratorModel->abandonPlacementProcedure();
        }
        if (boardConfiguratorModel->getState() != State::BoardReady) {
            if (!boardConfiguratorModel->isShipPlacerEmpty()) {
                boardConfiguratorModel->getShipPlacerController()->handleKeyPress(key, x, y);
            } else {
                boardConfiguratorModel->getShipContainerController()->handleKeyPress(key, x, y);
            }
        }
    }

private:
    BoardConfiguratorModel* boardConfiguratorModel; ///< Pointer to the board configurator model
};


#endif //UNTITLED_BOARDCONFIGURATORCONTROLLER_H
