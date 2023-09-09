//
// Created by gerdzio21 on 05.08.2023.
//

#ifndef UNTITLED_ONLINEGAMECONTROLLER_H
#define UNTITLED_ONLINEGAMECONTROLLER_H


#include "ConnectionManager.h"
#include "Response.h"
#include "../Game/GameModel.h"
#include "../GameElements/Coordinate.h"

class OnlineGameController {
    ConnectionManager* connectionManager;
    Response getResponse();
public:
    OnlineGameController(ConnectionManager* connectionManager1, bool hostGame);
    OnlineGameController();

    Response attack(Coordinate coordinate);
    Response getMove();

    void postAttackResult(AttackResult attackResult);

    void postAttackMove(char col, int row);

    std::string getAttackResult();

    void postSunk();

    void postHit();

    void postMissed();

    std::string getReadyForAnswering();

    void postReadyForAnswering();


    void postError();
};


#endif //UNTITLED_ONLINEGAMECONTROLLER_H
