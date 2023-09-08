#include "BoardConfiguratorModel.h"

//
// Created by Gerdzio21 on 2023-09-08.
//
BoardConfiguratorModel::BoardConfiguratorModel() : rows(10), columns(10) {
    shipPlacerController = new ShipPlacerController();
    shipContainerController = new ShipContainerController();
    board = new Board();
    state = State::SelectShip;
}

BoardConfiguratorModel::~BoardConfiguratorModel() {
    delete shipPlacerController;
    delete shipContainerController;
}

Board *BoardConfiguratorModel::getBoard() const {
    return board;
}

void BoardConfiguratorModel::placeShip() {
    placeShip(shipPlacerController->getShip(), shipPlacerController->getShipOrientation(),
              shipPlacerController->getHullPosition().col, shipPlacerController->getHullPosition().row);
}

void BoardConfiguratorModel::placeShip(Ship *ship, ShipOrientation shipOrientation, char hullCol, int hullRow) {
    bool placementSucceed = false;
    if (canPlaceShipAtThisPosition(hullCol, hullRow, ship->getLength(), shipOrientation)) {
        reserveArea(hullCol, hullRow, ship->getLength(), shipOrientation);
        board->addShipToBoard(ship);
        placeShipAtPosition(ship, hullCol, hullRow, shipOrientation);
        placementSucceed = true;
    }
    if (placementSucceed) {
        shipContainerController->removeSelectedShipFromContainer();
        shipPlacerController->emptyPlacer();
        if (shipContainerController->isEmpty()) {
            state = State::BoardReady;
        } else {
            state = State::SelectShip;
        }
    }
}

bool BoardConfiguratorModel::canPlaceShipAtThisPosition(char hullCol, int hullRow, int length,
                                                        ShipOrientation shipOrientation) {
    bool canPlaceShipAtThisPosition = true;
    for (int j = 0; j < length; j++) {
        FieldStatus fieldStatus = FieldStatus::Free;
        if (shipOrientation == ShipOrientation::Horizontal) {
            fieldStatus = board->getField(hullCol + j, hullRow)->getFieldStatus();
        } else if (shipOrientation == ShipOrientation::Vertical) {
            fieldStatus = board->getField(hullCol, hullRow + j)->getFieldStatus();
        }
        if (fieldStatus != FieldStatus::Free) {
            canPlaceShipAtThisPosition = false;
            break;
        }
    }
    return canPlaceShipAtThisPosition;
}

void BoardConfiguratorModel::reserveArea(char hullCol, int hullRow, int length, ShipOrientation shipOrientation) { // rectangle area
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= length; j++) {
            if (shipOrientation == ShipOrientation::Horizontal) {
                board->setFieldStatus(hullCol + j, hullRow + i, FieldStatus::SurroundsShip);
            } else if (shipOrientation == ShipOrientation::Vertical) {
                board->setFieldStatus(hullCol + i, hullRow + j, FieldStatus::SurroundsShip);
            }
        }
    }
}

void BoardConfiguratorModel::placeShipAtPosition(Ship *ship, char hullCol, int hullRow, ShipOrientation shipOrientation) {
    if (shipOrientation == ShipOrientation::Horizontal) {
        int i = 0;
        for (char col = hullCol; col < (char) (hullCol + ship->getLength()); col++) {
            board->placeShipSector(col, hullRow, ship, i);
            i++;
        }
    } else {
        int i = 0;
        for (int row = hullRow; row < (hullRow + ship->getLength()); row++) {
            board->placeShipSector(hullCol, row, ship, i);
            i++;
        }
    }
}

void BoardConfiguratorModel::selectShip() {
    Ship* selectedShip = shipContainerController->getSelectedShip();
    shipPlacerController->addShipToPlace(selectedShip);
    state = State::PlaceShip;
}

void BoardConfiguratorModel::abandonPlacementProcedure() {
    shipPlacerController->emptyPlacer();
    state = State::SelectShip;
}

bool BoardConfiguratorModel::isBoardReady() {
    return state == State::BoardReady;
}

bool BoardConfiguratorModel::isShipContainerEmpty() {
    return shipContainerController->isEmpty();
}

bool BoardConfiguratorModel::isShipPlacerEmpty() {
    return shipPlacerController->isPlacerEmpty();
}

void BoardConfiguratorModel::placeShipRandom() {
    srand(time(NULL));
    selectShip();
    state = State::PlaceShip;
    while (true) {
        if(state == State::PlaceShip) {
            char randCol = std::rand() % 10 + 'A';
            int randRow = std::rand() % 10 + 1;
            shipPlacerController->setCol(randCol);
            shipPlacerController->setRow(randRow);
            shipPlacerController->setOrientation(std::rand() % 2 == 0 ? Horizontal : Vertical);
            placeShip();
        }
        if (state == State::SelectShip) {
            shipContainerController->selectNextShip();
            selectShip();
        }
        if(state == State::BoardReady){
            break;
        }
    }
    state = State::BoardReady;
}

ShipContainerController *BoardConfiguratorModel::getShipContainerController() {
    return shipContainerController;
}

ShipPlacerController *BoardConfiguratorModel::getShipPlacerController() {
    return shipPlacerController;
}
