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
    Response getResponse(){
        return Response(connectionManager->receiveMessage());
    }
public:
    OnlineGameController(ConnectionManager* connectionManager1, bool hostGame){
        connectionManager = connectionManager1;
        if(hostGame){
            connectionManager->startServerGame();
        }else{
            std::string ipAddress;
            std::cin>>ipAddress;
            connectionManager->startClientGame(ipAddress.c_str(), 12345); //"127.0.0.1", 12345);
        }
    }
    OnlineGameController();

    Response attack(Coordinate coordinate){
        connectionManager->sendMessage("ATTACK:"+coordinate.toString());
        return getResponse();
    }
    Response getMove() {
        return getResponse();
    }

    void postAttackResult(AttackResult attackResult){
        connectionManager->sendMessage("RESULT:"+ AttackResultToString(attackResult));
    }

    void postAttackMove(char col, int row) {
        connectionManager->sendMessage(col + std::to_string(row));
    }

    std::string getAttackResult() {
        return connectionManager->receiveMessage();
    }

    void postSunk() {
        connectionManager->sendMessage("SUNK");
    }

    void postHit() {
        connectionManager->sendMessage("HIT");
    }

    void postMissed() {
        connectionManager->sendMessage("MISS");
    }

    std::string getReadyForAnswering() {
        return connectionManager->receiveMessage();
    }

    void postReadyForAnswering() {
        connectionManager->sendMessage("STATUS:CHANGE");
    }


    void postError() {
        connectionManager->sendMessage("RESPONSE_ERROR:ERROR");
    }
};


#endif //UNTITLED_ONLINEGAMECONTROLLER_H
