//
// Created by Gerdzio21 on 2023-09-08.
//
#include "ShipPlacerController.h"

void ShipPlacerController::setOrientation(ShipOrientation orientation) {
    shipOrientation = orientation;
}

void ShipPlacerController::setRow(int row) {
    hullCoordinate.row=row;
}

void ShipPlacerController::setCol(char col) {
    hullCoordinate.col=col;
}

ShipOrientation ShipPlacerController::getShipOrientation() {
    return shipOrientation;
}

Coordinate ShipPlacerController::getHullPosition() {
    return hullCoordinate;
}

Ship *ShipPlacerController::getShip() {
    return ship;
}

void ShipPlacerController::emptyPlacer() {
    shipOrientation = ShipOrientation::Horizontal;
    hullCoordinate = Coordinate('A', 1);
    ship = nullptr;
}

void ShipPlacerController::handleKeyPress(unsigned char key, int x, int y) {
    switch (tolower(key)) {
        case 'w':
            moveUp();
            break;
        case 's':
            moveDown();
            break;
        case 'a':
            moveLeft();
            break;
        case 'd':
            moveRight();
            break;
        case 'r':
            rotateShip();
            break;
    }
}

bool ShipPlacerController::isPlacerEmpty() {
    return ship == nullptr;
}

void ShipPlacerController::addShipToPlace(Ship *selectedShip) {
    ship = selectedShip;
}

ShipPlacerController::~ShipPlacerController() {
    delete ship;
}

ShipPlacerController::ShipPlacerController() {
    ship = nullptr;
}

void ShipPlacerController::rotateShip() {
    if ((hullCoordinate.col + ship->getLength() - 1) <= 'J' && (hullCoordinate.row + ship->getLength() - 1) <= 10) {
        shipOrientation = changeOrientation(shipOrientation);
    }
}

void ShipPlacerController::moveRight() {
    if (shipOrientation == ShipOrientation::Horizontal) {
        if ((hullCoordinate.col + ship->getLength() - 1) < 'J')
            hullCoordinate.col++;
    } else {
        if ((hullCoordinate.col) < 'J') {
            hullCoordinate.col++;
        }
    }
}

void ShipPlacerController::moveLeft() {
    if (hullCoordinate.col > 'A') {
        hullCoordinate.col--;
    }
}

void ShipPlacerController::moveDown() {
    if (shipOrientation == ShipOrientation::Horizontal) {
        if ((hullCoordinate.row) < 10)
            hullCoordinate.row++;
    } else {
        if ((hullCoordinate.row + ship->getLength() - 1) < 10) {
            hullCoordinate.row++;
        }
    }
}

void ShipPlacerController::moveUp() {
    if (hullCoordinate.row > 1) {
        hullCoordinate.row--;
    }
}
