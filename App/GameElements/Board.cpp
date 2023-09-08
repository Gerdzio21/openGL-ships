//
// Created by Gerdzio21 on 2023-09-08.
//
#include "Board.h"

void Board::addShipToAliveShips(Ship *ship) {
    shipsAlive.push_back(ship);
}

Board::~Board() {
    for (std::vector<Field*>& row: board) {
        for (Field* field: row) {
            delete field;
        }
        row.clear();
    }
    for (Ship* ship: shipsOnBoard) {
        delete ship;
    }
}

void Board::initializeField(char col, int row) {
    int x = (int) col - (int) 'A';
    int y = row - 1;
    board[y][x] = new Field();
}

Field *Board::getField(char col, int row) {
    if (col >= 'A' && col <= 'J' && row >= 1 && row <= 10) {
        int x = (int) col - (int) 'A';
        int y = row - 1;
        return board[y][x];
    }
    Field*  dumbField = new Field();
    dumbField->setFieldStatus(OccupiedByShip);
    return dumbField;
}

void Board::setFieldStatus(char col, int row, FieldStatus fieldStatus) {
    int x = (int) col - (int) 'A';
    int y = row - 1;
    if (y >= 0 && y < board.size()) {
        if (x >= 0 && board[y].size() > x) {
            board[y][x]->setFieldStatus(fieldStatus);
        } else {
            //std::cout<<"NO CHYBA NIE\n";
        }
    }

}

void Board::addShipToBoard(Ship *ship) {
    shipsOnBoard.push_back(ship);
    addShipToAliveShips(ship);
}

int Board::getNumberOfAliveShips() {
    return shipsAlive.size();
}

void Board::moveToDestroyedShips(Ship *ship) {
    auto it = std::find(shipsAlive.begin(), shipsAlive.end(), ship);
    if (it != shipsAlive.end()) {
        shipsAlive.erase(it);
    }
    shipsDestroyed.push_back(ship);
}

void Board::placeShipSector(char col, int row, Ship *ship, int shipSector) {
    int x = (int) col - (int) 'A';
    int y = row - 1;
    board[y][x]->placeShip(ship, shipSector);
}

Board::Board() : board(10, std::vector<Field*>(10)) {
    boardViewer = new BoardViewer();
    for (int i = (int) 'A'; i <= (int) 'J'; i++) {
        for (int j = 1; j <= 10; j++) {
            initializeField((char) i, j);
        }
    }
}

std::vector<std::vector<Field *>> Board::getBoardAsVector() {
    return board;
}
