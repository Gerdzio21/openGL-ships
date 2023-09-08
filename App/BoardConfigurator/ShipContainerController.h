//
// Created by gerdzio21 on 23.05.2023.
//

#ifndef SHIPS_SHIPCONTAINER_H
#define SHIPS_SHIPCONTAINER_H


#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include "../GameElements/Ships/Ship.h"
#include "../GameElements/Ships/ShipFactory.h"
#include "ShipContainerViewer.h"

/**
 * @class ShipContainerController
 * @brief Controller for ship container management.
 *
 * The `ShipContainerController` class is responsible for managing the ship container
 * in the game. It handles the selection, removal, and drawing of ships in the container.
 */
class ShipContainerController {
public:
    /**
     * Constructor for the `ShipContainerController` class.
     * Initializes the controller with an empty container and fills it with ships.
     */
    ShipContainerController();

    ~ShipContainerController();

    /**
        * @brief Get the currently selected ship.
        *
        * @return A pointer to the currently selected ship.
        * @throw std::out_of_range If the selected ship index is invalid.
        */
    Ship* getSelectedShip();

    /**
        * @brief Remove the currently selected ship from the container.
        *
        * If the selected ship is the last one in the container, the selected ship index
        * is updated accordingly.
        *
        * @throw std::out_of_range If the selected ship index is invalid.
        */
    void removeSelectedShipFromContainer();

    /**
 * @brief Check if the ship container is empty.
 *
 * @return True if the container is empty, false otherwise.
 */
    bool isEmpty();

    /**
        * @brief Select the next ship in the container.
        */
    void selectNextShip();

/**
     * @brief Select the previous ship in the container.
     */
    void selectPreviousShip();

    /**
   * @brief Get the index of the currently selected ship.
   *
   * @return The index of the currently selected ship.
   */
    int getSelectedShipIndex();

    /**
    * @brief Get a vector of all ships in the container.
    *
    * @return A vector containing pointers to all the ships in the container.
    */
    std::vector<Ship*> getShips();;

    /**
   * @brief Handle keyboard key presses for ship selection.
   *
   * @param key The pressed key (usually 'w' or 's' for ship selection).
   * @param x The x-coordinate of the key press.
   * @param y The y-coordinate of the key press.
   */
    void handleKeyPress(unsigned char key, int x, int y);

private:
    /**
    * @brief Empty the ship container.
    */
    void emptyContainer();

    /**
        * @brief Fill the ship container with ships.
        */
    void fillContainer();

private:
    std::vector<Ship*> ships;            ///< Vector of pointers to ships in the container.
    int selectedShipIndex;              ///< Index of the currently selected ship.
    ShipFactory* factory;               ///< Factory for creating ships.
};


#endif //SHIPS_SHIPCONTAINER_H
