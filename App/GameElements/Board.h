//
// Created by gerdzio21 on 13.08.2023.
//

#ifndef UNTITLED_BOARD_H
#define UNTITLED_BOARD_H


#include <vector>
#include "Field.h"
#include "FieldViewer.h"
#include "BoardViewer.h"

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
    void addShipToAliveShips(Ship* ship) {
        shipsAlive.push_back(ship);
    }


public:
    /**
     * @brief Destructor for the `Board` class.
     */
    ~Board() {
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

    /**
    * @brief Initialize a field on the board.
    *
    * @param col The column of the field.
    * @param row The row of the field.
    */
    void initializeField(char col, int row) {
        int x = (int) col - (int) 'A';
        int y = row - 1;
        board[y][x] = new Field();
    }

    /**
    * @brief Get a field at a specific location on the board.
    *
    * @param col The column of the field.
    * @param row The row of the field.
    * @return Pointer to the field if it exists, otherwise nullptr.
    */
    Field* getField(char col, int row) {
        if (col >= 'A' && col <= 'J' && row >= 1 && row <= 10) {
            int x = (int) col - (int) 'A';
            int y = row - 1;
            return board[y][x];
        }
        return nullptr;
    }

    /**
    * @brief Set the status of a field on the board.
    *
    * @param col The column of the field.
    * @param row The row of the field.
    * @param fieldStatus The status to set on the field.
    */
    void setFieldStatus(char col, int row, FieldStatus fieldStatus) {
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

    /**
    * @brief Add a ship to the board.
    *
    * @param ship The ship to add.
    */
    void addShipToBoard(Ship* ship) {
        shipsOnBoard.push_back(ship);
        addShipToAliveShips(ship);
    }

    /**
     * @brief Get the number of alive ships on the board.
     *
     * @return The number of alive ships.
     */
    int getNumberOfAliveShips() {
        return shipsAlive.size();
    }

    /**
    * @brief Move a ship to the list of destroyed ships.
    *
    * @param ship The ship to move to the list of destroyed ships.
    */
    void moveToDestroyedShips(Ship* ship) {
        auto it = std::find(shipsAlive.begin(), shipsAlive.end(), ship);
        if (it != shipsAlive.end()) {
            shipsAlive.erase(it);
        }
        shipsDestroyed.push_back(ship);
    }

    /**
        * @brief Place a ship sector on the board.
        *
        * @param col The column where the sector will be placed.
        * @param row The row where the sector will be placed.
        * @param ship The ship to which the sector belongs.
        * @param shipSector The index of the ship sector to place.
        */
    void placeShipSector(char col, int row, Ship* ship, int shipSector) {
        int x = (int) col - (int) 'A';
        int y = row - 1;
        board[y][x]->placeShip(ship, shipSector);
    }

    /**
    * @brief Constructor for the `Board` class.
    *
    * Initializes the game board and its fields.
    */
    Board() : board(10, std::vector<Field*>(10)) {
        boardViewer = new BoardViewer();
        for (int i = (int) 'A'; i <= (int) 'J'; i++) {
            for (int j = 1; j <= 10; j++) {
                initializeField((char) i, j);
            }
        }
    }

public:
    /**
 * @brief Get the board as a 2D vector of fields.
 *
 * @return The board as a 2D vector of fields.
 */
    std::vector<std::vector<Field*>> getBoardAsVector() {
        return board;
    }
};


#endif //UNTITLED_BOARD_H
