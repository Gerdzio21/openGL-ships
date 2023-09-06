//
// Created by gerdzio21 on 06.08.2023.
//

#ifndef UNTITLED_BOARDCONFIGURATORMODEL_H
#define UNTITLED_BOARDCONFIGURATORMODEL_H

#include "ShipPlacerController.h"
#include "ShipContainerController.h"

enum State {
    PlaceShip,
    SelectShip,
    BoardReady,
};

/**
 * @class BoardConfiguratorModel
 * @brief Model for board configuration.
 *
 * The `BoardConfiguratorModel` class represents the model responsible for
 * handling the board configuration in the game. It contains methods and
 * data related to configuring the game board.
 */
class BoardConfiguratorModel {

public:
    /**
    * Constructor for the `BoardConfiguratorModel` class.
    * Initializes the model with default values.
    */
    BoardConfiguratorModel() : rows(10), columns(10) {
        shipPlacerController = new ShipPlacerController();
        shipContainerController = new ShipContainerController();
        board = new Board();
        state = State::SelectShip;
    }

    /**
   * Destructor for the `BoardConfiguratorModel` class.
   * Cleans up dynamically allocated resources.
   */
    ~BoardConfiguratorModel() {
        delete shipPlacerController;
        delete shipContainerController;
    }

    /**
   * Get a pointer to the game board.
   * @return Pointer to the game board.
   */
    Board* getBoard() const {
        return board;
    }

    /**
       * Places a ship on the game board.
       */
    void placeShip() {
        placeShip(shipPlacerController->getShip(), shipPlacerController->getShipOrientation(),
                  shipPlacerController->getHullPosition().col, shipPlacerController->getHullPosition().row);
    }

    /**
        * Places a ship on the game board.
        * @param ship The ship to be placed.
        * @param shipOrientation The orientation of the ship (horizontal or vertical).
        * @param hullCol The column of the hull position.
        * @param hullRow The row of the hull position.
        */
    void placeShip(Ship* ship, ShipOrientation shipOrientation, char hullCol, int hullRow) {
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

    /**
        * Checks if it's possible to place a ship at the given position.
        * @param hullCol The column of the hull position.
        * @param hullRow The row of the hull position.
        * @param length The length of the ship.
        * @param shipOrientation The orientation of the ship (horizontal or vertical).
        * @return True if the ship can be placed at the position; false otherwise.
        */
    bool
    canPlaceShipAtThisPosition(char hullCol, int hullRow, int length, ShipOrientation shipOrientation) {
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

    /**
           * Reserves area for place a ship at the given position.
           * @param hullCol The column of the hull position.
           * @param hullRow The row of the hull position.
           * @param length The length of the ship.
           * @param shipOrientation The orientation of the ship (horizontal or vertical).
           */
    void reserveArea(char hullCol, int hullRow, int length, ShipOrientation shipOrientation) { // rectangle area
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

    /**
         * Place a ship at the given position.
         * @param hullCol The column of the hull position.
         * @param hullRow The row of the hull position.
         * @param length The length of the ship.
         * @param shipOrientation The orientation of the ship (horizontal or vertical).
         */

    void placeShipAtPosition(Ship* ship, char hullCol, int hullRow, ShipOrientation shipOrientation) {
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

    /**
         * Moves ship form ShipContainer to ShipPlacer and changing state to PlaceShip
         */
    void selectShip() {
        Ship* selectedShip = shipContainerController->getSelectedShip();
        shipPlacerController->addShipToPlace(selectedShip);
        state = State::PlaceShip;
    }

    /**
        * Abandon place procedure
        */
    void abandonPlacementProcedure() {
        shipPlacerController->emptyPlacer();
        state = State::SelectShip;
    }

    /**
          * Give information is board ready to play. All ships are on board
          * @return True if the board is ready; false otherwise.
          */
    bool isBoardReady() {
        return state == State::BoardReady;
    }

    /**
        * Get the current state of the board configuration.
        * @return The current state (PlaceShip, SelectShip, BoardReady).
        */
    State getState() {
        return state;
    }

    /**
          * Give information is shipContainer empty
          * @return True if empty; false otherwise.
          */
    bool isShipContainerEmpty() {
        return shipContainerController->isEmpty();
    }

    /**
        * Give information is shipPlacer empty
        * @return True if empty; false otherwise.
        */
    bool isShipPlacerEmpty() {
        return shipPlacerController->isPlacerEmpty();
    }

    ShipPlacerController* getShipPlacerController() {
        return shipPlacerController;
    }

    ShipContainerController* getShipContainerController() {
        return shipContainerController;
    }

private:
    const int columns;///< The number of columns on the game board.
    const int rows;///< The number of rows on the game board.
    Board* board; ///< Pointer to the game board.
    ShipPlacerController* shipPlacerController;///< Pointer to the ship placer controller.
    ShipContainerController* shipContainerController;///< Pointer to the ship container controller.
    State state;///< The current state of board configuration.
};


#endif //UNTITLED_BOARDCONFIGURATORMODEL_H
