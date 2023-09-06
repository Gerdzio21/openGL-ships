//
// Created by gerdzio21 on 06.08.2023.
//

#ifndef UNTITLED_GAMECONTROLLER_H
#define UNTITLED_GAMECONTROLLER_H

#include <GL/freeglut.h>
#include "../WebServices/OnlineGameController.h"
#include "GameModel.h"
#include "GameViewer.h"

#include "../WebServices/ConnectionManager.h"

#include "../GameElements/Board.h"


/**
 * @class GameController
 * @brief Controller for managing game interactions.
 *
 * The `GameController` class is responsible for managing user inputs and game logic
 * in the context of a game. It handles key presses, game state transitions, and communication
 * with an online opponent.
 */
class GameController : public SceneController {
public:
    /**
    * @brief Handle keyboard key presses.
    *
    * @param key The pressed key.
    * @param x The x-coordinate of the key press.
    * @param y The y-coordinate of the key press.
    */
    void handleKeyPress(unsigned char key, int x, int y) {
        if (key == 8) {
            gameModel->removeFromText();//text.pop_back();
        } else if (key == 13) {
            enterMove();
        } else {
            gameModel->clearMessage();
            gameModel->textAppend((char) toupper(key));
        }
    }

    /**
    * @brief Constructor for the `GameController` class.
    *
    * @param gameModelPtr Pointer to the associated `GameModel` object.
    */
    GameController(GameModel* gameModelPtr) {
        gameModel = gameModelPtr;
    }

    /**
        * @brief Create a new game.
        *
        * Initializes the online game controller, sets the opponent's turn, and starts the game.
        */
    void createGame() {
        onlineGameController = new OnlineGameController(new ConnectionManager, true);
        gameModel->setOpponentTurn();
        getOpponentMove();
    } /**
     * @brief Join an existing game.
     *
     * Initializes the online game controller for joining an existing game.
     */
    void joinGame() {
        onlineGameController = new OnlineGameController(new ConnectionManager, false);
    }

    /**
        * @brief Process the user's move input.
        *
        * Parses and validates the move input, then sends it to the opponent for processing.
        */
    void enterMove() {
        Coordinate coordinates = Coordinate(gameModel->getText());
        if (gameModel->isAttackMoveValid(coordinates)) {
            gameModel->clearText();
            Response response = onlineGameController->attack(coordinates);
            processAttackResponse(response, coordinates);
        } else {
            wrongMove();
        }
    } /**
     * @brief Process the response from an attack move.
     *
     * Updates the game state based on the response received from the opponent.
     *
     * @param response The response from the opponent.
     * @param coordinate The coordinate of the attack move.
     */
    void processAttackResponse(Response response, Coordinate coordinate) {
        if (response.type == ResponseType::RESULT) {
            if (gameModel->getTurn() == LOCAL_PLAYER) {
                AttackResult attackResult = mapStringToAttackResult(response.body);
                gameModel->processAttackResult(attackResult, coordinate);
                if (gameModel->getTurn() == OPPONENT) {
                    onlineGameController->postReadyForAnswering();
                    getOpponentMove();
                } else if (gameModel->getTurn() == END) {
                    gameModel->setMessage("GAME END");
                }
            }
        } else {
            processResponse(response);
        }
    } /**
     * @brief Get the opponent's move.
     *
     * Requests the opponent's move from the online game controller.
     */
    void getOpponentMove() {
        Response response = onlineGameController->getMove();
        processOpponentAttack(response);
    }

    /**
    * @brief Process the opponent's attack move.
    *
    * Updates the game state based on the opponent's attack move and sends the result back.
    *
    * @param response The response from the opponent.
    */
    void processOpponentAttack(Response response) {
        if (response.type == ResponseType::ATTACK) {
            if (gameModel->getTurn() == OPPONENT) {
                AttackResult attackResult = gameModel->processOpponentAttack(response.body);
                onlineGameController->postAttackResult(attackResult);
                if (gameModel->getTurn() == LOCAL_PLAYER) {
                    onlineGameController->getReadyForAnswering();
                } else if (gameModel->getTurn() == END) {
                    gameModel->setMessage("GAME END");
                } else {
                    getOpponentMove();
                }
            }
        } else {
            processResponse(response);
        }
    }

    /**
    * @brief Process responses from the opponent.
    *
    * Handles responses from the opponent when it's not an attack move.
    *
    * @param response The response from the opponent.
    */
    void processResponse(Response response) {
        if (gameModel->getTurn() == OPPONENT) {
            onlineGameController->postError();
            getOpponentMove();
        }
    }

    /**
     * @brief Handle an incorrect move input.
     *
     * Clears the text input and displays an error message.
     */
    void wrongMove() {
        gameModel->clearText();//.clear();
        gameModel->setMessage("WRONG MOVE!");
    }

private:
    GameModel* gameModel; ///< Pointer to the associated `GameModel` object.
    OnlineGameController* onlineGameController; ///< Pointer to the online game controller.
};


#endif //UNTITLED_GAMECONTROLLER_H
