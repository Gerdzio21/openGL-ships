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
    ShipContainerController() {
        emptyContainer();
        fillContainer();
        selectedShipIndex = 0;
    }

    ~ShipContainerController() {
        for (Ship* ship: ships) {
            delete ship;
        }
    }

    /**
        * @brief Get the currently selected ship.
        *
        * @return A pointer to the currently selected ship.
        * @throw std::out_of_range If the selected ship index is invalid.
        */
    Ship* getSelectedShip() {
        if (selectedShipIndex < 0 || selectedShipIndex >= ships.size()) {
            throw std::out_of_range("Invalid ship index");
        }
        return ships[selectedShipIndex];
    }

    /**
        * @brief Remove the currently selected ship from the container.
        *
        * If the selected ship is the last one in the container, the selected ship index
        * is updated accordingly.
        *
        * @throw std::out_of_range If the selected ship index is invalid.
        */
    void removeSelectedShipFromContainer() {
        if (selectedShipIndex < 0 || selectedShipIndex >= ships.size()) {
            throw std::out_of_range("Invalid ship index");
        }
        if (selectedShipIndex == ships.size() - 1) {
            ships.erase(ships.begin() + selectedShipIndex);
            selectedShipIndex--; //ujemny index oznacza, że już nie ma statków
        } else {
            ships.erase(ships.begin() + selectedShipIndex);
        }


    }

    /**
 * @brief Check if the ship container is empty.
 *
 * @return True if the container is empty, false otherwise.
 */
    bool isEmpty() {
        return ships.empty();
    }

    /**
        * @brief Select the next ship in the container.
        */
    void selectNextShip() {
        selectedShipIndex = (selectedShipIndex + 1) % ships.size();
    }

/**
     * @brief Select the previous ship in the container.
     */
    void selectPreviousShip() {
        if (selectedShipIndex == 0) {
            selectedShipIndex = ships.size() - 1;
        } else {
            selectedShipIndex = (selectedShipIndex - 1) % ships.size();
        }
    }

    /**
   * @brief Get the index of the currently selected ship.
   *
   * @return The index of the currently selected ship.
   */
    int getSelectedShipIndex() {
        return selectedShipIndex;
    }

    /**
    * @brief Get a vector of all ships in the container.
    *
    * @return A vector containing pointers to all the ships in the container.
    */
    std::vector<Ship*> getShips() {
        return ships;
    };

    /**
   * @brief Handle keyboard key presses for ship selection.
   *
   * @param key The pressed key (usually 'w' or 's' for ship selection).
   * @param x The x-coordinate of the key press.
   * @param y The y-coordinate of the key press.
   */
    void handleKeyPress(unsigned char key, int x, int y) {
        switch (tolower(key)) {
            case 'w':
                selectNextShip();
                break;
            case 's':
                selectPreviousShip();
                break;
        }
    }

private:
    /**
    * @brief Empty the ship container.
    */
    void emptyContainer() {
        ships.clear();
    }

    /**
        * @brief Fill the ship container with ships.
        */
    void fillContainer() {
        factory = new AircraftCarrierFactory();
        for (int i = 0; i < 1; i++) {
            ships.push_back(factory->createShip());
        }
        factory = new BattleshipFactory();
        for (int i = 0; i < 2; i++) {
            ships.push_back(factory->createShip());
        }
        factory = new CruiserFactory();
        for (int i = 0; i < 2; i++) {
            ships.push_back(factory->createShip());
        }
        factory = new FrigateFactory();
        for (int i = 0; i < 3; i++) {
            ships.push_back(factory->createShip());
        }
    }

private:
    std::vector<Ship*> ships;            ///< Vector of pointers to ships in the container.
    int selectedShipIndex;              ///< Index of the currently selected ship.
    ShipFactory* factory;               ///< Factory for creating ships.
};


#endif //SHIPS_SHIPCONTAINER_H
