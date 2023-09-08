//
// Created by gerdzio21 on 06.08.2023.
//

#ifndef UNTITLED_BOARDCONFIGURATORMODEL_H
#define UNTITLED_BOARDCONFIGURATORMODEL_H

#include "ShipPlacerController.h"
#include "ShipContainerController.h"
#include "../GameElements/Board.h"

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
    BoardConfiguratorModel();

    /**
   * Destructor for the `BoardConfiguratorModel` class.
   * Cleans up dynamically allocated resources.
   */
    ~BoardConfiguratorModel();

    /**
   * Get a pointer to the game board.
   * @return Pointer to the game board.
   */
    Board* getBoard() const;

    /**
       * Places a ship on the game board.
       */
    void placeShip();

    /**
        * Places a ship on the game board.
        * @param ship The ship to be placed.
        * @param shipOrientation The orientation of the ship (horizontal or vertical).
        * @param hullCol The column of the hull position.
        * @param hullRow The row of the hull position.
        */
    void placeShip(Ship* ship, ShipOrientation shipOrientation, char hullCol, int hullRow);

    /**
        * Checks if it's possible to place a ship at the given position.
        * @param hullCol The column of the hull position.
        * @param hullRow The row of the hull position.
        * @param length The length of the ship.
        * @param shipOrientation The orientation of the ship (horizontal or vertical).
        * @return True if the ship can be placed at the position; false otherwise.
        */
    bool
    canPlaceShipAtThisPosition(char hullCol, int hullRow, int length, ShipOrientation shipOrientation);

    /**
           * Reserves area for place a ship at the given position.
           * @param hullCol The column of the hull position.
           * @param hullRow The row of the hull position.
           * @param length The length of the ship.
           * @param shipOrientation The orientation of the ship (horizontal or vertical).
           */
    void reserveArea(char hullCol, int hullRow, int length, ShipOrientation shipOrientation);

    /**
         * Place a ship at the given position.
         * @param hullCol The column of the hull position.
         * @param hullRow The row of the hull position.
         * @param length The length of the ship.
         * @param shipOrientation The orientation of the ship (horizontal or vertical).
         */

    void placeShipAtPosition(Ship* ship, char hullCol, int hullRow, ShipOrientation shipOrientation);

    /**
         * Moves ship form ShipContainer to ShipPlacer and changing state to PlaceShip
         */
    void selectShip();

    /**
        * Abandon place procedure
        */
    void abandonPlacementProcedure();

    /**
          * Give information is board ready to play. All ships are on board
          * @return True if the board is ready; false otherwise.
          */
    bool isBoardReady();

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
    bool isShipContainerEmpty();

    /**
        * Give information is shipPlacer empty
        * @return True if empty; false otherwise.
        */
    bool isShipPlacerEmpty();

    ShipPlacerController* getShipPlacerController();

    ShipContainerController* getShipContainerController();

    void placeShipRandom();

private:
    const int columns;///< The number of columns on the game board.
    const int rows;///< The number of rows on the game board.
    Board* board; ///< Pointer to the game board.
    ShipPlacerController* shipPlacerController;///< Pointer to the ship placer controller.
    ShipContainerController* shipContainerController;///< Pointer to the ship container controller.
    State state;///< The current state of board configuration.
};


#endif //UNTITLED_BOARDCONFIGURATORMODEL_H
