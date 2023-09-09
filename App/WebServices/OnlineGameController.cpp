#include "OnlineGameController.h"

//
// Created by Gerdzio21 on 2023-09-09.
//
Response OnlineGameController::getResponse() {
    return Response(connectionManager->receiveMessage());
}

OnlineGameController::OnlineGameController(ConnectionManager *connectionManager1, bool hostGame) {
    connectionManager = connectionManager1;
    if(hostGame){
        connectionManager->startServerGame();
    }else{
        std::string ipAddress;
        std::cin>>ipAddress;
        connectionManager->startClientGame(ipAddress.c_str(), 12345); //"127.0.0.1", 12345);
    }
}

Response OnlineGameController::attack(Coordinate coordinate) {
    connectionManager->sendMessage("ATTACK:"+coordinate.toString());
    return getResponse();
}

Response OnlineGameController::getMove() {
    return getResponse();
}

void OnlineGameController::postAttackResult(AttackResult attackResult) {
    connectionManager->sendMessage("RESULT:"+ AttackResultToString(attackResult));
}

void OnlineGameController::postAttackMove(char col, int row) {
    connectionManager->sendMessage(col + std::to_string(row));
}

std::string OnlineGameController::getAttackResult() {
    return connectionManager->receiveMessage();
}

void OnlineGameController::postSunk() {
    connectionManager->sendMessage("SUNK");
}

void OnlineGameController::postHit() {
    connectionManager->sendMessage("HIT");
}

void OnlineGameController::postMissed() {
    connectionManager->sendMessage("MISS");
}

std::string OnlineGameController::getReadyForAnswering() {
    return connectionManager->receiveMessage();
}

void OnlineGameController::postReadyForAnswering() {
    connectionManager->sendMessage("STATUS:CHANGE");
}

void OnlineGameController::postError() {
    connectionManager->sendMessage("RESPONSE_ERROR:ERROR");
}
