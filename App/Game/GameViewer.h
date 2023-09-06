//
// Created by gerdzio21 on 05.08.2023.
//

#ifndef UNTITLED_GAMEVIEWER_H
#define UNTITLED_GAMEVIEWER_H


#include "GameModel.h"
#include "../SceneViewer.h"

/**
 * @class GameViewer
 * @brief Viewer for displaying the game interface.
 *
 * The `GameViewer` class is responsible for rendering the game interface, including game boards,
 * text input, and messages displayed during the game.
 */
class GameViewer : public SceneViewer {
    /**
       * @brief Constructor for the `GameViewer` class.
       *
       * @param gameModelPtr Pointer to the game model.
       */

public:
    GameViewer(GameModel* gameModelPtr) {
        gameModel = gameModelPtr;
        boardViewer = new BoardViewer();
    }

    /**
     * @brief Display the game scene.
     *
     * Renders the local player's game board, opponent's game board, text input, and messages.
     */
    virtual void displayScene() {
        boardViewer->drawBoard(-10, 10, gameModel->getLocalPlayerBoard()->getBoardAsVector());
        boardViewer->drawBoard(1, 10, gameModel->getOpponentBoard()->getBoardAsVector());
        display(300, 200, gameModel->getText());
        display(300, 100, gameModel->getMessage());
    }

/**
     * @brief Draw text on the screen.
     *
     * @param x The x-coordinate for the text.
     * @param y The y-coordinate for the text.
     * @param text The text to display.
     */
    void drawText(int x, int y, const std::string& text) {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, 600, 0, 600); // Współrzędne okna
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        int textWidth = 0;
        for (char c: text) {
            textWidth += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, c);
        }
        int xOffset = x - textWidth / 2;
        glRasterPos2i(xOffset, y);
        for (char c: text) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
    }

    /**
        * @brief Display text on the screen.
        *
        * @param x The x-coordinate for the text.
        * @param y The y-coordinate for the text.
        * @param text The text to display.
        */
    void display(int x, int y, std::string text) {
        glColor3f(1.0f, 0.0f, 1.0f);
        drawText(x, y, text);
    }

private:
    GameModel* gameModel; ///< Pointer to the game model.
    BoardViewer* boardViewer;
};


#endif //UNTITLED_GAMEVIEWER_H
