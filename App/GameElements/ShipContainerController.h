//
// Created by gerdzio21 on 23.05.2023.
//

#ifndef SHIPS_SHIPCONTAINER_H
#define SHIPS_SHIPCONTAINER_H


#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include "Ships/Ship.h"
#include "Ships/ShipFactory.h"
#include "ShipContainerViewer.h"

class ShipContainerController {
    std::vector<Ship*> ships;
    int selectedShipIndex;
    ShipContainerViewer* shipContainerViewer;
    ShipFactory* factory;

public:
    ShipContainerController() {
        shipContainerViewer =new ShipContainerViewer();
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

    void drawContainer(){
        shipContainerViewer->drawContainer(-5,-5);
        int x = -10;
        int y = 1;
        if(!ships.empty()) {
            Ship* previousShip = ships[0];
            for (auto ship: ships) {
                if (previousShip != ship) {
                    if (x + previousShip->getLength() + ship->getLength() < 11) {
                        x = x + previousShip->getLength() + 1;
                    } else {
                        x = -10;
                        y = y + 2;
                    }
                }
                if (ship == ships[selectedShipIndex]) {
                    ship->drawShipOutline(x, y, ShipOrientation::Horizontal);
                } else {
                    ship->drawShip(x, y, ShipOrientation::Horizontal);
                }
                previousShip = ship;
            }
        }
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
};


#endif //SHIPS_SHIPCONTAINER_H
