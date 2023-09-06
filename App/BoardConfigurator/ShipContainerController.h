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
        shipContainerViewer = new ShipContainerViewer();
        emptyContainer();
        fillContainer();
        selectedShipIndex  = 0;
    }
    ~ShipContainerController(){
        for (Ship* ship : ships){
            delete ship;
        }
    }

    Ship* getSelectedShip() {
        if (selectedShipIndex < 0 || selectedShipIndex >= ships.size()) {
            throw std::out_of_range("Invalid ship index");
        }
        return ships[selectedShipIndex];
    }

    void removeSelectedShipFromContainer() {
        if (selectedShipIndex < 0 || selectedShipIndex >= ships.size()) {
            throw std::out_of_range("Invalid ship index");
        }
            if(selectedShipIndex == ships.size()-1){
                ships.erase(ships.begin()+selectedShipIndex);
                selectedShipIndex --; //ujemny index oznacza, że już nie ma statków
            } else{
                ships.erase(ships.begin()+selectedShipIndex);
            }


        }
    bool isEmpty(){
        return ships.empty();
    }

    void selectNextShip() {
        selectedShipIndex=(selectedShipIndex+1)%ships.size();
    }

    void selectPreviousShip() {
        if(selectedShipIndex==0){
            selectedShipIndex = ships.size()-1;
        }else{
            selectedShipIndex=(selectedShipIndex-1)%ships.size();
        }
    }
    int getSelectedShipIndex(){
        return selectedShipIndex;
    }
    std::vector<Ship*> getShips(){
        return ships;
    };
    void handleKeyPress(unsigned char key, int x, int y) {
        switch (tolower(key)){
            case 'w':
                selectNextShip();
                break;
            case 's':
                selectPreviousShip();
                break;
        }
    }
private:
    void emptyContainer(){
        ships.clear();
    }

    void fillContainer(){
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
    std::vector<Ship*> ships;
    int selectedShipIndex;
    ShipContainerViewer* shipContainerViewer;
    ShipFactory* factory;
};


#endif //SHIPS_SHIPCONTAINER_H
