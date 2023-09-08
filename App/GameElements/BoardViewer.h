//
// Created by gerdzio21 on 13.08.2023.
//

#ifndef UNTITLED_BOARDVIEWER_H
#define UNTITLED_BOARDVIEWER_H

#include <Gl/freeglut.h>
#include <vector>
#include "Field.h"
#include "FieldViewer.h"


/**
 * @class BoardViewer
 * @brief Handles rendering of the game board.
 *
 * The `BoardViewer` class is responsible for rendering the game board, including its fields and their statuses.
 */
class BoardViewer {
public:
    /**
     * @brief Draw the game board.
     *
     * @param x The x-coordinate for rendering the board.
     * @param y The y-coordinate for rendering the board.
     * @param board The 2D vector representing the game board.
     */
    void drawBoard(int x, int y, std::vector<std::vector<Field*>> board);
};


#endif //UNTITLED_BOARDVIEWER_H
