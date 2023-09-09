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
    GameViewer(GameModel* gameModelPtr);

    /**
     * @brief Display the game scene.
     *
     * Renders the local player's game board, opponent's game board, text input, and messages.
     */
    virtual void displayScene();

/**
     * @brief Draw text on the screen.
     *
     * @param x The x-coordinate for the text.
     * @param y The y-coordinate for the text.
     * @param text The text to display.
     */
    void drawText(int x, int y, const std::string& text);

    /**
        * @brief Display text on the screen.
        *
        * @param x The x-coordinate for the text.
        * @param y The y-coordinate for the text.
        * @param text The text to display.
        */
    void display(int x, int y, std::string text);

private:
    GameModel* gameModel; ///< Pointer to the game model.
    BoardViewer* boardViewer;
};


#endif //UNTITLED_GAMEVIEWER_H
