//
// Created by gerdzio21 on 23.05.2023.
//

#ifndef SHIPS_SHIPPLACER_H
#define SHIPS_SHIPPLACER_H


#include "Ships/Ship.h"
#include "ShipOrientation.h"
#include "Coordinate.h"

class ShipPlacerController {
    Ship* ship;
    ShipOrientation shipOrientation = ShipOrientation::Horizontal;
    Coordinate hullCoordinate  = Coordinate('A',1);;


    void moveUp() {
        if(hullCoordinate.row>1) {
            hullCoordinate.row--;
        }
    }
    void moveDown() {
        if(shipOrientation==ShipOrientation::Horizontal){
            if((hullCoordinate.row)<10)
                hullCoordinate.row++;
        }else{
            if((hullCoordinate.row+ship->getLength()-1)<10){
                hullCoordinate.row++;
            }
        }
    }
    void moveLeft() {
        if(hullCoordinate.col>'A') {
            hullCoordinate.col--;
        }
    }

    void moveRight() {
        if(shipOrientation==ShipOrientation::Horizontal){
            if((hullCoordinate.col+ship->getLength()-1)<'J' )
                hullCoordinate.col++;
        }else{
            if((hullCoordinate.col)<'J'){
                hullCoordinate.col++;
            }
        }
    }

    void rotateShip() {
        if((hullCoordinate.col+ship->getLength()-1)<='J' && (hullCoordinate.row+ship->getLength()-1)<=10){
            shipOrientation = changeOrientation(shipOrientation);
        }
    }
public:
    ShipPlacerController(){
        ship = nullptr;
    }
    ~ShipPlacerController(){
        delete ship;
    }
    void addShipToPlace(Ship* selectedShip){
        ship = selectedShip;
    }

    bool isPlacerEmpty(){
        return ship == nullptr;
    }

    void handleKeyPress(unsigned char key, int x, int y) {
        switch (tolower(key)){
            case 'w':
               moveUp();
               break;
            case 's':
                moveDown();
                break;
            case 'a':
                moveLeft();
                break;
            case'd':
                moveRight();
                break;
            case 'r':
                rotateShip();
                break;
        }
    }

    void drawShip(int x,int y) {
        ship->drawShip(x+(hullCoordinate.col-'A'),-y+hullCoordinate.row-1,shipOrientation,0.2123f,0.0303f, 0.78731233f);
    }

    void emptyPlacer(){
        shipOrientation = ShipOrientation::Horizontal;
        hullCoordinate  = Coordinate('A',1);
        ship = nullptr;
    }

    void printHullPosition() {
        std::cout<<hullCoordinate.col << " " << hullCoordinate.row<<'\n';

    }
    void addShip(Ship* ship1){
        ship = ship1;
    }

    Ship* getShip() {
        return ship;
    }
    Coordinate getHullPosition(){
        return hullCoordinate;
    }
    ShipOrientation getShipOrientation(){
        return shipOrientation;
    }
};


#endif //SHIPS_SHIPPLACER_H
