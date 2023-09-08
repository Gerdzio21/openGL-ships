#include "BoardConfiguratorViewer.h"

//
// Created by Gerdzio21 on 2023-09-08.
//
BoardConfiguratorViewer::BoardConfiguratorViewer(BoardConfiguratorModel *boardConfiguratorModelPtr) {
    boardConfiguratorModel = boardConfiguratorModelPtr;
    boardViewer = new BoardViewer();
    shipContainerViewer = new ShipContainerViewer();
    shipPlacerViewer = new ShipPlacerViewer();
}

void BoardConfiguratorViewer::displayScene() {
    boardViewer->drawBoard(-5, 10, boardConfiguratorModel->getBoard()->getBoardAsVector());
    shipContainerViewer->drawContainer(boardConfiguratorModel->getShipContainerController()->getShips(),
                                       boardConfiguratorModel->getShipContainerController()->getSelectedShipIndex());
    shipPlacerViewer->drawShipToPlace(boardConfiguratorModel->getShipPlacerController());
}
