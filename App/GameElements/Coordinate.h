//
// Created by gerdzio21 on 15.08.2023.
//

#ifndef UNTITLED_COORDINATE_H
#define UNTITLED_COORDINATE_H


struct Coordinate {
    Coordinate(char col, int row) : col(col), row(row){};
    explicit Coordinate (std::string coordinates){
        col = getCol(coordinates);
        row = getRow(coordinates);
    }

    char col;
    int row;

    char getCol(std::string move){
        return move[0];
    }
    int getRow(std::string move){
        int number = 0;
        for (int i = 1; i<move.length(); i++) {
            number = number * 10 + (move[i] - '0');
        }
        return number;
    }
    std::string toString(){
        return col + std::to_string(row);
    }
};


#endif //UNTITLED_COORDINATE_H
