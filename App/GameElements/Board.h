//
// Created by gerdzio21 on 13.08.2023.
//

#ifndef UNTITLED_BOARD_H
#define UNTITLED_BOARD_H


#include <vector>
#include "Field.h"
#include "FieldViewer.h"
#include "BoardViewer.h"
#include <algorithm>

/**
 * @class Board
 * @brief Represents the game board.
 *
 * The `Board` class manages the game board, including fields, ships, and their statuses.
 */
class Board {
private:

    BoardViewer* boardViewer;            ///< Viewer for rendering the board.
    std::vector<std::vector<Field*>> board;  ///< 2D vector representing the game board.
    std::vector<Ship*> shipsOnBoard;     ///< List of ships currently placed on the board.
    std::vector<Ship*> shipsAlive;       ///< List of ships that are still alive.
    std::vector<Ship*> shipsDestroyed;   ///< List of ships that have been destroyed.

    /**
     * @brief Add a ship to the list of alive ships.
     *
     * @param ship The ship to add.
     */
    void addShipToAliveShips(Ship* ship);


public:
    /**
     * @brief Destructor for the `Board` class.
     */
    ~Board();

    /**
    * @brief Initialize a field on the board.
    *
    * @param col The column of the field.
    * @param row The row of the field.
    */
    void initializeField(char col, int row);

    /**
    * @brief Get a field at a specific location on the board.
    *
    * @param col The column of the field.
    * @param row The row of the field.
    * @return Pointer to the field if it exists, otherwise nullptr.
    */
    Field* getField(char col, int row);

    /**
    * @brief Set the status of a field on the board.
    *
    * @param col The column of the field.
    * @param row The row of the field.
    * @param fieldStatus The status to set on the field.
    */
    void setFieldStatus(char col, int row, FieldStatus fieldStatus);

    /**
    * @brief Add a ship to the board.
    *
    * @param ship The ship to add.
    */
    void addShipToBoard(Ship* ship);

    /**
     * @brief Get the number of alive ships on the board.
     *
     * @return The number of alive ships.
     */
    int getNumberOfAliveShips();

    /**
    * @brief Move a ship to the list of destroyed ships.
    *
    * @param ship The ship to move to the list of destroyed ships.
    */
    void moveToDestroyedShips(Ship* ship);

    /**
        * @brief Place a ship sector on the board.
        *
        * @param col The column where the sector will be placed.
        * @param row The row where the sector will be placed.
        * @param ship The ship to which the sector belongs.
        * @param shipSector The index of the ship sector to place.
        */
    void placeShipSector(char col, int row, Ship* ship, int shipSector);

    /**
    * @brief Constructor for the `Board` class.
    *
    * Initializes the game board and its fields.
    */
    Board();

public:
    /**
 * @brief Get the board as a 2D vector of fields.
 *
 * @return The board as a 2D vector of fields.
 */
    std::vector<std::vector<Field*>> getBoardAsVector();
};


#endif //UNTITLED_BOARD_H
