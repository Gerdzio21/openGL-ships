//
// Created by gerdzio21 on 15.08.2023.
//

#ifndef UNTITLED_COORDINATE_H
#define UNTITLED_COORDINATE_H
#include <string>
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
    Coordinate(char col, int row);;

    /**
   * @brief Constructor to initialize a Coordinate from a string representation.
   * @param coordinates The string representation of the coordinate (e.g., "A1").
   */
    explicit Coordinate(std::string coordinates);

    char col;
    int row;

    /**
        * @brief Get the column (char) from a string representation.
        * @param move The string representation of the coordinate (e.g., "A1").
        * @return The column (char) extracted from the string.
        */
    char getCol(std::string move);

    /**
    * @brief Get the row (int) from a string representation.
    * @param move The string representation of the coordinate (e.g., "A1").
    * @return The row (int) extracted from the string.
    */
    int getRow(std::string move);

    /**
    * @brief Convert the coordinate to its string representation (e.g., "A1").
    * @return The string representation of the coordinate.
    */
    std::string toString();
};


#endif //UNTITLED_COORDINATE_H
