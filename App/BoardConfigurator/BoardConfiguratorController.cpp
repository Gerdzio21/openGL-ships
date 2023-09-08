//
// Created by Gerdzio21 on 2023-09-08.
//
#include "BoardConfiguratorController.h"

void BoardConfiguratorController::handleKeyPress(unsigned char key, int x, int y) {
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
        if (key == 'q'){
            boardConfiguratorModel->placeShipRandom();
        }
        else if (!boardConfiguratorModel->isShipPlacerEmpty()) {
            boardConfiguratorModel->getShipPlacerController()->handleKeyPress(key, x, y);
        } else {
            boardConfiguratorModel->getShipContainerController()->handleKeyPress(key, x, y);
        }
    }
}
