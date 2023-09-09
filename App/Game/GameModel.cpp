//
// Created by Gerdzio21 on 2023-09-09.
//
#include "GameModel.h"
AttackResult mapStringToAttackResult(const std::string &input) {
    if (input == "HIT") {
        return HIT;
    } else if (input == "MISS") {
        return MISS;
    } else if (input == "SUNK") {
        return SUNK;
    } else if (input == "GAME_END") {
        return GAME_END;
    }
    return HIT;
}

std::string AttackResultToString(AttackResult enumValue) {
    static std::map<AttackResult, std::string> enumMap = {
            {HIT,  "HIT"},
            {MISS, "MISS"},
            {SUNK, "SUNK"}
    };

    auto it = enumMap.find(enumValue);
    if (it != enumMap.end()) {
        return it->second;
    }
    return "Unknown"; // Możesz zwrócić odpowiednią wartość domyślną
}

GameModel::GameModel(Board *localPlayerBoardPtr) {
    localPlayerBoard = localPlayerBoardPtr;
    opponentBoard = new Board();
    turn = LOCAL_PLAYER;
}

bool GameModel::isAttackMoveValid(Coordinate coordinate) {
    return (coordinate.col >= 'A' && coordinate.col <= 'J' && coordinate.row >= 1 && coordinate.row <= 10);
}

Turn GameModel::getTurn() {
    return turn;
}

void GameModel::setOpponentTurn() {
    turn = OPPONENT;
}

void GameModel::processAttackResult(AttackResult result, Coordinate coordinate) {
    if (result == HIT || result == SUNK) {
        markField(opponentBoard->getField(coordinate.col, coordinate.row), "HIT");
    } else if (result == MISS) {
        markField(opponentBoard->getField(coordinate.col, coordinate.row), "MISS");
        turn = OPPONENT;
    } else if (result == GAME_END) {
        turn = END;
    }
}

AttackResult GameModel::processOpponentAttack(std::string potentialCoordinates) {
    Coordinate coordinates = Coordinate(potentialCoordinates);
    if (isAttackMoveValid(coordinates)) {
        Field* field = localPlayerBoard->getField(coordinates.col, coordinates.row);
        if (field != nullptr) {
            if (field->getFieldStatus() == FieldStatus::OccupiedByShip) {
                int sectorIdx = field->getShipSectorIdx();
                Ship* ship = field->getShip();
                ship->hitSector(sectorIdx);
                markField(localPlayerBoard->getField(coordinates.col, coordinates.row), "HIT");
                if (ship->isDestroyed()) {
                    localPlayerBoard->moveToDestroyedShips(ship);
                    if (localPlayerBoard->getNumberOfAliveShips() == 0) {
                        turn = END;
                        return GAME_END;
                    }
                    return SUNK;
                }
                return HIT;
            } else if (field->getFieldStatus() == FieldStatus::Free ||
                       field->getFieldStatus() == FieldStatus::SurroundsShip) {
                markField(localPlayerBoard->getField(coordinates.col, coordinates.row), "MISS");
                turn = LOCAL_PLAYER;
                return MISS;
            }
        }
    }
    return GAME_END;
}

Board *GameModel::getLocalPlayerBoard() {
    return localPlayerBoard;
}

Board *GameModel::getOpponentBoard() {
    return opponentBoard;
}

void GameModel::setMessage(std::string msg) {
    message = msg;
}

void GameModel::clearText() {
    text.clear();
}

void GameModel::clearMessage() {
    message.clear();
}

std::string GameModel::getText() {
    return text;
}

void GameModel::textAppend(char c) {
    text += c;
}

void GameModel::removeFromText() {
    if (!text.empty()) {
        text.pop_back();
    }
}

std::string GameModel::getMessage() {
    return message;
}

void GameModel::markField(Field *field, std::string attackResult) {
    if (attackResult == "HIT") {
        field->setFieldStatus(FieldStatus::Hit);
    } else {
        field->setFieldStatus(FieldStatus::Missed);
    }
}
