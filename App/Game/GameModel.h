//
// Created by gerdzio21 on 05.08.2023.
//

#ifndef UNTITLED_GAMEMODEL_H
#define UNTITLED_GAMEMODEL_H


#include <vector>
#include <iostream>
#include <map>
#include "../GameElements/Board.h"
#include "../GameElements/Coordinate.h"

/**
 * @enum AttackResult
 * @brief Enumerates possible attack results.
 */
enum AttackResult {
    HIT,        ///< The attack resulted in a hit.
    MISS,       ///< The attack resulted in a miss.
    SUNK,       ///< The attack resulted in a ship sinking.
    GAME_END,   ///< The game has ended.
};

/**
 * @brief Map a string to an AttackResult enum.
 *
 * @param input The input string to map.
 * @return The corresponding AttackResult enum value.
 */
AttackResult mapStringToAttackResult(const std::string& input);

/**
 * @brief Convert an AttackResult enum to a string.
 *
 * @param enumValue The AttackResult enum value.
 * @return The string representation of the enum value.
 */
std::string AttackResultToString(AttackResult enumValue);

/**
 * @enum Turn
 * @brief Enumerates the possible player turns.
 */
enum Turn {
    LOCAL_PLAYER,     ///< Local player's turn.
    OPPONENT,         ///< Opponent's turn.
    END,              ///< Game has ended.
};
/**
 * @enum GameState
 * @brief Enumerates the possible game states.
 */
enum GameState {
    ATTACKING,            ///< Attacking phase.
    DEFENSE,              ///< Defense phase.
    WAITING_FOR_OPPONENT, ///< Waiting for opponent's move.

};
/**
 * @enum EndGameReason
 * @brief Enumerates possible reasons for the end of the game.
 */
enum EndGameReason {
    YOU_WIN,                ///< You won the game.
    YOU_LOOSE,              ///< You lost the game.
    PLAYER_DISCONNECTED,    ///< Opponent disconnected.
};

/**
 * @class GameModel
 * @brief Model for managing game state and logic.
 *
 * The `GameModel` class is responsible for managing the game's state, including player turns, attack results,
 * and the game boards. It also handles text input and messages displayed during the game.
 */
class GameModel {

public:
    /**
     * @brief Constructor for the `GameModel` class.
     *
     * @param localPlayerBoardPtr Pointer to the local player's game board.
     */
    GameModel(Board* localPlayerBoardPtr);

    /**
   * @brief Check if an attack move is valid.
   *
   * @param coordinate The coordinate of the attack move.
   * @return True if the attack move is valid, false otherwise.
   */
    bool isAttackMoveValid(Coordinate coordinate);

    /**
    * @brief Get the current player's turn.
    *
    * @return The current player's turn.
    */
    Turn getTurn();

    /**
     * @brief Set the turn to the opponent's turn.
     */
    void setOpponentTurn();

    /**
    * @brief Process the result of an attack move.
    *
    * Updates the game state based on the attack result and coordinate of the attack.
    *
    * @param result The result of the attack move.
    * @param coordinate The coordinate of the attack.
    */
    void processAttackResult(AttackResult result, Coordinate coordinate);

    /**
    * @brief Process the opponent's attack move.
    *
    * Updates the game state based on the opponent's attack move.
    *
    * @param potentialCoordinates The potential attack coordinates from the opponent.
    * @return The result of the opponent's attack.
    */
    AttackResult processOpponentAttack(std::string potentialCoordinates);

    /**
        * @brief Get the local player's game board.
        *
        * @return Pointer to the local player's game board.
        */
    Board* getLocalPlayerBoard();

    /**
    * @brief Get the opponent's game board.
    *
    * @return Pointer to the opponent's game board.
    */
    Board* getOpponentBoard();

/**
     * @brief Destructor for the `GameModel` class.
     */
    ~GameModel() = default;

    /**
        * @brief Set a message to display in the game.
        *
        * @param msg The message to display.
        */
    void setMessage(std::string msg);

/**
     * @brief Clear the text input.
     */
    void clearText();

    /**
     * @brief Clear the message displayed in the game.
     */
    void clearMessage();

    /**
        * @brief Get the current text input.
        *
        * @return The current text input.
        */
    std::string getText();

    /**
        * @brief Append a character to the text input.
        *
        * @param c The character to append.
        */
    void textAppend(char c);

    /**
        * @brief Remove the last character from the text input.
        */
    void removeFromText();

    /**
        * @brief Get the current message displayed in the game.
        *
        * @return The current message displayed in the game.
        */
    std::string getMessage();

private:
    Board* localPlayerBoard;    ///< Pointer to the local player's game board.
    Board* opponentBoard;       ///< Pointer to the opponent's game board.
    Turn turn;                  ///< The current player's turn.
    std::string text = "";      ///< The current text input.
    std::string message = "";   ///< The current message displayed in the game.

    /**
     * @brief Mark a game field with a specific attack result.
     *
     * @param field The game field to mark.
     * @param attackResult The attack result to set on the field.
     */
    void markField(Field* field, std::string attackResult);
};


#endif //UNTITLED_GAMEMODEL_H
