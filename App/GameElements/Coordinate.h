//
// Created by gerdzio21 on 15.08.2023.
//

#ifndef UNTITLED_COORDINATE_H
#define UNTITLED_COORDINATE_H

/**
 * @struct Coordinate
 * @brief Represents a coordinate on the game board.
 *
 * The `Coordinate` struct represents a coordinate on the game board, consisting of a column (char) and a row (int).
 */
struct Coordinate {
    /**
     * @brief Constructor to initialize a Coordinate with a column and row.
     * @param col The column (char) of the coordinate.
     * @param row The row (int) of the coordinate.
     */
    Coordinate(char col, int row) : col(col), row(row) {};

    /**
   * @brief Constructor to initialize a Coordinate from a string representation.
   * @param coordinates The string representation of the coordinate (e.g., "A1").
   */
    explicit Coordinate(std::string coordinates) {
        col = getCol(coordinates);
        row = getRow(coordinates);
    }

    char col;
    int row;

    /**
        * @brief Get the column (char) from a string representation.
        * @param move The string representation of the coordinate (e.g., "A1").
        * @return The column (char) extracted from the string.
        */
    char getCol(std::string move) {
        return move[0];
    }

    /**
    * @brief Get the row (int) from a string representation.
    * @param move The string representation of the coordinate (e.g., "A1").
    * @return The row (int) extracted from the string.
    */
    int getRow(std::string move) {
        int number = 0;
        for (int i = 1; i < move.length(); i++) {
            number = number * 10 + (move[i] - '0');
        }
        return number;
    }

    /**
    * @brief Convert the coordinate to its string representation (e.g., "A1").
    * @return The string representation of the coordinate.
    */
    std::string toString() {
        return col + std::to_string(row);
    }
};


#endif //UNTITLED_COORDINATE_H
