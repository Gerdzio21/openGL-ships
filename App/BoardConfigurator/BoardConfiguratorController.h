//
// Created by gerdzio21 on 06.08.2023.
//

#ifndef UNTITLED_BOARDCONFIGURATORCONTROLLER_H
#define UNTITLED_BOARDCONFIGURATORCONTROLLER_H


#include "BoardConfiguratorModel.h"
#include "BoardConfiguratorViewer.h"
#include "../GameElements/Board.h"
#include "../GameElements/Ships/Ship.h"
#include "../GameElements/ShipOrientation.h"
#include "../GameElements/ShipPlacerController.h"
#include "../GameElements/ShipContainerController.h"
#include "../SceneController.h"

enum State {
    PlaceShip,
    SelectShip,
    BoardReady,
};


class BoardConfiguratorController : public SceneController{

public:
    const int columns;
    const int rows;
    Board* board;
    ShipPlacerController* shipPlacerController;
    State state;
    ShipContainerController* shipContainerController;

    public:

    virtual void handleKeyPress(unsigned char key, int x, int y) {
        if(key==13){  //ENTER
            if(state == State::SelectShip){
                if(!shipContainerController->isEmpty()){
                    selectShip();
                }

            }else if(state==State::PlaceShip){
                placeShip(shipPlacerController->getShip(),shipPlacerController->getShipOrientation(), shipPlacerController->getHullPosition().col, shipPlacerController->getHullPosition().row);
            }
        }else if (key == 27){  //ESCAPE
            abandonPlacementProcedure();
        }
        if(state != State::BoardReady) {
            if (!shipPlacerController->isPlacerEmpty()) {
                shipPlacerController->handleKeyPress(key, x, y);
            } else {
                shipContainerController->handleKeyPress(key, x, y);
            }
        }
    }


    BoardConfiguratorController() : rows(10), columns(10) {
            boardConfiguratorViewer = new BoardConfiguratorViewer();
            shipPlacerController = new ShipPlacerController();
            shipContainerController = new ShipContainerController();
            board = new Board();
            state = State::SelectShip;
    }
    ~BoardConfiguratorController(){
        delete board;
        delete shipPlacerController;
        delete shipContainerController;
    }
    Board*  getBoard() const {
        return board;
    }

    void placeShip(Ship* ship, ShipOrientation shipOrientation, char hullCol, int hullRow) {
            bool placementSucceed = false;
            if (canPlaceShipAtThisPosition(hullCol, hullRow, ship->getLength(), shipOrientation)) {
                reserveArea(hullCol, hullRow, ship->getLength(), shipOrientation);
                board->addShipToBoard(ship);
                placeShipAtPosition(ship, hullCol, hullRow, shipOrientation);
                placementSucceed = true;
            }
            if(placementSucceed) {
                shipContainerController->removeSelectedShipFromContainer();
                shipPlacerController->emptyPlacer();
                if (shipContainerController->isEmpty()) {
                    state = State::BoardReady;
                } else {
                    state = State::SelectShip;
                }
            }else{
                std::cout<<"CAN'T PLACE";
            }
        }

        bool
        canPlaceShipAtThisPosition(char hullCol,int hullRow, int length, ShipOrientation shipOrientation) {
            bool canPlaceShipAtThisPosition = true;
            for(int j = 0; j< length; j++){
                FieldStatus fieldStatus = FieldStatus::Free;
                if(shipOrientation==ShipOrientation::Horizontal){
                   fieldStatus = board->getField(hullCol+j,hullRow)->getFieldStatus();
                }else if (shipOrientation==ShipOrientation::Vertical){
                    fieldStatus = board->getField(hullCol,hullRow+j)->getFieldStatus();
                }
                if(fieldStatus != FieldStatus::Free){
                    canPlaceShipAtThisPosition = false;
                    break;
                }
            }
            return canPlaceShipAtThisPosition;
        }

        void reserveArea(char hullCol,int hullRow, int length, ShipOrientation shipOrientation) { // rectangle area
                for (int i = -1; i<=1; i++){
                    for(int j = -1; j<= length; j++){
                        if(shipOrientation==ShipOrientation::Horizontal){
                            board->setFieldStatus(hullCol+j,hullRow+i,FieldStatus::SurroundsShip);
                        }else if (shipOrientation==ShipOrientation::Vertical){
                            board->setFieldStatus(hullCol+i,hullRow+j,FieldStatus::SurroundsShip);
                        }
                    }
                }
        }


        void placeShipAtPosition(Ship* ship, char hullCol, int hullRow, ShipOrientation shipOrientation) {
            if (shipOrientation == ShipOrientation::Horizontal) {
                int i = 0;
                for(char col = hullCol; col<(char)(hullCol+ship->getLength()); col++){
                    board->placeShipSector(col, hullRow, ship, i);
                    i++;
                }
            } else {
                int i = 0;
                for(int row = hullRow; row<(hullRow+ship->getLength()); row++){
                    board->placeShipSector(hullCol, row, ship, i);
                    i++;
                }
            }
        }

    void selectShip() {
        Ship* selectedShip = shipContainerController->getSelectedShip();
        shipPlacerController->addShipToPlace(selectedShip);
        state = State::PlaceShip;
    }
    void abandonPlacementProcedure(){
        shipPlacerController->emptyPlacer();
        state = State::SelectShip;
    }

    bool isBoardReady(){
        return state == State::BoardReady;
    }
    void showBoard() {
        board->drawBoard(-5,10);
        shipContainerController->drawContainer();
        if(!shipPlacerController->isPlacerEmpty()){
            shipPlacerController->drawShip(-5,10);
        }
    }

private:
    BoardConfiguratorModel boardConfiguratorModel;
    BoardConfiguratorViewer* boardConfiguratorViewer;
};


#endif //UNTITLED_BOARDCONFIGURATORCONTROLLER_H
