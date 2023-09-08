

//
// Created by Gerdzio21 on 2023-09-08.
//
#include "Coordinate.h"
Coordinate::Coordinate(char col, int row) : col(col), row(row) {}

Coordinate::Coordinate(std::string coordinates) {
    col = getCol(coordinates);
    row = getRow(coordinates);
}

char Coordinate::getCol(std::string move) {
    return move[0];
}

int Coordinate::getRow(std::string move) {
    int number = 0;
    for (int i = 1; i < move.length(); i++) {
        number = number * 10 + (move[i] - '0');
    }
    return number;
}

std::string Coordinate::toString() {
    return col + std::to_string(row);
}
