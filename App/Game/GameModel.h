//
// Created by gerdzio21 on 05.08.2023.
//

#ifndef UNTITLED_GAMEMODEL_H
#define UNTITLED_GAMEMODEL_H


#include <vector>
#include <iostream>
#include <map>
#include "GameController.h"
enum AttackResult {
    HIT,
    MISS,
    SUNK,
    GAME_END,
};

AttackResult mapStringToAttackResult(const std::string& input) {
    if (input == "HIT") {
        return HIT;
    } else if (input == "MISS") {
        return MISS;
    } else if (input == "SUNK") {
        return SUNK;
    } else if (input =="GAME_END"){
        return GAME_END;
    }
    return HIT;
}
std::string AttackResultToString(AttackResult enumValue) {
    static std::map<AttackResult, std::string> enumMap  = {
            {HIT, "HIT"},
            {MISS, "MISS"},
            {SUNK, "SUNK"}
    };

    auto it = enumMap.find(enumValue);
    if (it != enumMap.end()) {
        return it->second;
    }
    return "Unknown"; // Możesz zwrócić odpowiednią wartość domyślną
}
enum Turn {
    LOCAL_PLAYER,
    OPPONENT,
    END,
};
enum GameState {
    ATTACKING,
    DEFENSE,
    WAITING_FOR_OPPONENT,
};
enum EndGameReason {
    YOU_WIN,
    YOU_LOOSE,
    PLAYER_DISCONNECTED
};
class GameModel { ;

    ~GameModel() = default;

public:
    GameModel(Board* playerBoard, Board* opponentBoard ) : playerBoard(playerBoard), opponentBoard(opponentBoard){
        turn = LOCAL_PLAYER;
    }
    void setUserBoard(Board* board){
        playerBoard = board;
    }
    bool isAttackMoveValid(Coordinate coordinate){
       return (coordinate.col >= 'A' && coordinate.col <= 'J' && coordinate.row>=1 && coordinate.row<=10);
    }
    Turn getTurn() {
        return turn;
    }
    void setOpponentTurn(){
        turn = OPPONENT;
    }
    void processAttackResult(AttackResult result, Coordinate coordinate){
        if(result == HIT || result == SUNK) {
            markField(opponentBoard->getField(coordinate.col, coordinate.row), "HIT");
        }else if(result == MISS){
            markField(opponentBoard->getField(coordinate.col, coordinate.row), "MISS");
            turn = OPPONENT;
        }else if(result == GAME_END){
            turn = END;
        }
    }
    AttackResult processOpponentAttack(std::string potentialCoordinates) {
        Coordinate coordinates = Coordinate(potentialCoordinates);
        if(isAttackMoveValid(coordinates)) {
            Field* field = playerBoard->getField(coordinates.col, coordinates.row);
            if (field != nullptr) {
                if (field->getFieldStatus() == FieldStatus::OccupiedByShip) {
                    int sectorIdx = field->getShipSectorIdx();
                    Ship* ship = field->getShip();
                    ship->hitSector(sectorIdx);
                    markField(playerBoard->getField(coordinates.col, coordinates.row), "HIT");
                    if(ship->isDestroyed()){
                        playerBoard->moveToDestroyedShips(ship);
                        if(playerBoard->getNumberOfAliveShips() == 0){
                            turn = END;
                            return GAME_END;
                        }
                        return SUNK;
                    }
                    return HIT;
                } else if (field->getFieldStatus() == FieldStatus::Free || field->getFieldStatus() == FieldStatus::SurroundsShip){
                    markField(playerBoard->getField(coordinates.col, coordinates.row), "MISS");
                    turn = LOCAL_PLAYER;
                    return MISS;
                }
            }
        }
    }

private:
    Board* playerBoard;
    Board* opponentBoard;
    Turn turn;

    void markField(Field* field, std::string attackResult) {
        if (attackResult =="HIT"){
            field->setFieldStatus(FieldStatus::Hit);
        }else{
            field->setFieldStatus(FieldStatus::Missed);
        }
    }
};


#endif //UNTITLED_GAMEMODEL_H
