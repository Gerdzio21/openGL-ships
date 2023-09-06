//
// Created by gerdzio21 on 23.05.2023.
//

#ifndef SHIPS_SHIPPLACER_H
#define SHIPS_SHIPPLACER_H


#include "../GameElements/Ships/Ship.h"
#include "../GameElements/ShipOrientation.h"
#include "../GameElements/Coordinate.h"

/**
 * @class ShipPlacerController
 * @brief Controller for ship placement on the game board.
 *
 * The `ShipPlacerController` class is responsible for managing the placement of ships
 * on the game board. It allows moving, rotating, and adding ships to be placed.
 */
class ShipPlacerController {
    Ship* ship; ///< Pointer to the ship to be placed.
    ShipOrientation shipOrientation = ShipOrientation::Horizontal; ///< Current ship orientation.
    Coordinate hullCoordinate = Coordinate('A', 1); ///< Coordinate of the hull of the ship to be placed.


    /**
       * @brief Move the ship up on the game board.
       */
    void moveUp() {
        if (hullCoordinate.row > 1) {
            hullCoordinate.row--;
        }
    }

    /**
     * @brief Move the ship down on the game board.
     */
    void moveDown() {
        if (shipOrientation == ShipOrientation::Horizontal) {
            if ((hullCoordinate.row) < 10)
                hullCoordinate.row++;
        } else {
            if ((hullCoordinate.row + ship->getLength() - 1) < 10) {
                hullCoordinate.row++;
            }
        }
    }

    /**
    * @brief Move the ship left on the game board.
    */
    void moveLeft() {
        if (hullCoordinate.col > 'A') {
            hullCoordinate.col--;
        }
    }

/**
     * @brief Move the ship right on the game board.
     */
    void moveRight() {
        if (shipOrientation == ShipOrientation::Horizontal) {
            if ((hullCoordinate.col + ship->getLength() - 1) < 'J')
                hullCoordinate.col++;
        } else {
            if ((hullCoordinate.col) < 'J') {
                hullCoordinate.col++;
            }
        }
    }

    /**
        * @brief Rotate the ship (change its orientation) on the game board.
        */
    void rotateShip() {
        if ((hullCoordinate.col + ship->getLength() - 1) <= 'J' && (hullCoordinate.row + ship->getLength() - 1) <= 10) {
            shipOrientation = changeOrientation(shipOrientation);
        }
    }

public:
    /**
    * @brief Constructor for the `ShipPlacerController` class.
    *
    * Initializes the controller with no ship to place.
    */
    ShipPlacerController() {
        ship = nullptr;
    }

    /**
     * @brief Destructor for the `ShipPlacerController` class.
     *
     * Deletes the dynamically allocated ship object if one is present.
     */
    ~ShipPlacerController() {
        delete ship;
    }

    /**
     * @brief Add a ship to be placed on the game board.
     *
     * @param selectedShip Pointer to the ship to be placed.
     */
    void addShipToPlace(Ship* selectedShip) {
        ship = selectedShip;
    }

    /**
        * @brief Check if the ship placement controller is empty (no ship to place).
        *
        * @return True if no ship is currently set for placement, false otherwise.
        */
    bool isPlacerEmpty() {
        return ship == nullptr;
    }

    /**
        * @brief Handle keyboard key presses for ship placement.
        *
        * @param key The pressed key (e.g., 'w' for up, 's' for down).
        * @param x The x-coordinate of the key press.
        * @param y The y-coordinate of the key press.
        */
    void handleKeyPress(unsigned char key, int x, int y) {
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

    /**
       * @brief Reset the ship placement controller to an empty state.
       */
    void emptyPlacer() {
        shipOrientation = ShipOrientation::Horizontal;
        hullCoordinate = Coordinate('A', 1);
        ship = nullptr;
    }

/**
     * @brief Get the ship currently set for placement.
     *
     * @return Pointer to the ship to be placed.
     */
    Ship* getShip() {
        return ship;
    }

    /**
     * @brief Get the hull position (coordinate) of the ship to be placed.
     *
     * @return The coordinate of the ship's hull.
     */
    Coordinate getHullPosition() {
        return hullCoordinate;
    }

    /**
    * @brief Get the current orientation of the ship to be placed.
    *
    * @return The orientation of the ship.
    */
    ShipOrientation getShipOrientation() {
        return shipOrientation;
    }
};


#endif //SHIPS_SHIPPLACER_H