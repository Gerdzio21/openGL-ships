//
// Created by gerdzio21 on 13.08.2023.
//

#ifndef UNTITLED_BOARD_H
#define UNTITLED_BOARD_H


#include <vector>
#include "Field.h"
#include "FieldViewer.h"
#include "BoardViewer.h"

class Board {
private:

    BoardViewer* boardViewer;
    std::vector<std::vector<Field*>> board;
    std::vector<Ship*> shipsOnBoard;
    std::vector<Ship*> shipsAlive;
    std::vector<Ship*> shipsDestroyed;

    void addShipToAliveShips(Ship* ship){
        shipsAlive.push_back(ship);
    }


public:
    ~Board(){
        for (std::vector<Field*>& row : board) {
            for (Field* field : row) {
                delete field;
            }
            row.clear();
        }
        for (Ship* ship : shipsOnBoard){
            delete ship;
        }
    }
    void initializeField(char col, int row) {
        int x = (int) col - (int) 'A';
        int y = row-1;
        board[y][x] = new Field();
    }
    Field* getField(char col, int row) {
        if (col >= 'A' && col <= 'J' && row >= 1 && row <= 10) {
            int x = (int) col - (int) 'A';
            int y = row-1;
            return board[y][x];
        }
        return nullptr;
    }
    void setFieldStatus(char col, int row, FieldStatus fieldStatus) {
        int x = (int) col - (int) 'A';
        int y = row-1;
        if (y>=0 && y<board.size()){
            if(x >= 0 && board[y].size()>x){
                board[y][x] ->setFieldStatus(fieldStatus);
            }
            else{
                //std::cout<<"NO CHYBA NIE\n";
            }
        }

    }
    void addShipToBoard(Ship* ship){
        shipsOnBoard.push_back(ship);
        addShipToAliveShips(ship);
    }
    int getNumberOfAliveShips(){
        return shipsAlive.size();
    }
    void moveToDestroyedShips(Ship* ship){
        auto it = std::find(shipsAlive.begin(), shipsAlive.end(), ship);
        if (it != shipsAlive.end()) {
            shipsAlive.erase(it);
        }
        shipsDestroyed.push_back(ship);
    }

    void placeShipSector(char col, int row, Ship* ship, int shipSector) {
        int x = (int) col - (int) 'A';
        int y = row-1;
        board[y][x] ->placeShip(ship,shipSector);
    }
    Board() : board(10, std::vector<Field*>(10)){
        boardViewer = new BoardViewer();
        for(int i = (int)'A'; i<=(int)'J'; i++){
            for (int j = 1; j<=10; j++){
                initializeField((char)i, j);
            }
        }
    }
    void testShipReplacement(){
        setFieldStatus('B',2,FieldStatus::OccupiedByShip);
        setFieldStatus('B',3,FieldStatus::OccupiedByShip);
        setFieldStatus('B',4,FieldStatus::OccupiedByShip);
        setFieldStatus('B',5,FieldStatus::OccupiedByShip);
        setFieldStatus('B',6,FieldStatus::OccupiedByShip);
        setFieldStatus('B',8,FieldStatus::OccupiedByShip);
        setFieldStatus('B',9,FieldStatus::OccupiedByShip);
        setFieldStatus('D',8,FieldStatus::OccupiedByShip);
        setFieldStatus('D',9,FieldStatus::OccupiedByShip);
        setFieldStatus('F',8,FieldStatus::OccupiedByShip);
        setFieldStatus('F',9,FieldStatus::OccupiedByShip);
        setFieldStatus('H',7,FieldStatus::OccupiedByShip);
        setFieldStatus('H',8,FieldStatus::OccupiedByShip);
        setFieldStatus('D',6,FieldStatus::OccupiedByShip);
        setFieldStatus('E',6,FieldStatus::OccupiedByShip);
        setFieldStatus('F',6,FieldStatus::OccupiedByShip);
        setFieldStatus('E',4,FieldStatus::OccupiedByShip);
        setFieldStatus('F',4,FieldStatus::OccupiedByShip);
        setFieldStatus('G',4,FieldStatus::OccupiedByShip);
        setFieldStatus('H',4,FieldStatus::OccupiedByShip);
        setFieldStatus('D',2,FieldStatus::OccupiedByShip);
        setFieldStatus('E',2,FieldStatus::OccupiedByShip);
        setFieldStatus('F',2,FieldStatus::OccupiedByShip);
        setFieldStatus('G',2,FieldStatus::OccupiedByShip);
    }

public:
    void drawBoard(int x, int y) {
        boardViewer->drawBoard(x, y, board);
    }
    bool isAllFieldFreeInRectangleArea(char leftTopCornerCol,
                                       int leftTopCornerRow,
                                       char rightDownCornerCol,
                                       int rightDownCornerRow) { // rectangle area
        bool allFieldFreeInRectangleArea = true;
        for(int i = leftTopCornerRow; i<=rightDownCornerRow; i++){
            for(char j=leftTopCornerCol; j<=rightDownCornerCol; j++){
                if(!getField(j,i)->isFree()){
                    allFieldFreeInRectangleArea = false;
                    break;
                }
            }
        }
        return allFieldFreeInRectangleArea;
    }
};


#endif //UNTITLED_BOARD_H
