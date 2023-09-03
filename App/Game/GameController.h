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



class GameController: public SceneController{
public:
    void handleKeyPress(unsigned char key, int x, int y) {
        if (key == 8 && !text.empty()) {
            text.pop_back();
        } else if (key == 13) {
            enterMove();
        } else {
            message.clear();
            text += (char) toupper(key);
        }
    }
    GameController(){
        playerBoard = new Board();
        opponentBoard = new Board();
        gameModel = new GameModel(playerBoard, opponentBoard);
    }

    void setUserBoard(Board* board){
        playerBoard = board;
        gameModel ->setUserBoard(board);
    }

    void createGame(){
        onlineGameController = new OnlineGameController(new ConnectionManager, true);
        gameModel->setOpponentTurn();
        getOpponentMove();
    }
    void joinGame(){
        onlineGameController = new OnlineGameController(new ConnectionManager, false);
    }

    void enterMove() {
        Coordinate coordinates = Coordinate(text);
        if(gameModel->isAttackMoveValid(coordinates)){
            text.clear();
            Response response = onlineGameController->attack(coordinates);
            processAttackResponse(response, coordinates);
        }else{
            wrongMove();
        }
    }
    void processAttackResponse(Response response, Coordinate coordinate){
        if(response.type == ResponseType::RESULT){
            if(gameModel->getTurn() == LOCAL_PLAYER){
                AttackResult attackResult = mapStringToAttackResult(response.body);
                gameModel->processAttackResult(attackResult, coordinate);
                if(gameModel->getTurn() == OPPONENT){
                    onlineGameController->postReadyForAnswering();
                    getOpponentMove();
                }else if(gameModel->getTurn() == END){
                    message = "GAME END";
                }
            }
        }else{
            processResponse(response);
        }
    }
    void getOpponentMove(){
        Response response = onlineGameController->getMove();
        processOpponentAttack(response);
    }
    void processOpponentAttack(Response response){
        if(response.type == ResponseType::ATTACK){
            if(gameModel->getTurn() == OPPONENT){
                AttackResult attackResult = gameModel->processOpponentAttack(response.body);
                onlineGameController->postAttackResult(attackResult);
                if(gameModel->getTurn() == LOCAL_PLAYER){
                    onlineGameController->getReadyForAnswering();
                } else if(gameModel->getTurn() == END){
                    message = "GAME END";
                }else{
                    getOpponentMove();
                }
            }
        }else{
            processResponse(response);
        }
    }
    void processResponse(Response response){
        if(gameModel->getTurn() == OPPONENT){
            onlineGameController->postError();
            getOpponentMove();
        }
    }
    void wrongMove() {
        text.clear();
        message = "WRONG MOVE!";
    }


    void showGame() {
        playerBoard->drawBoard(-10, 10);
        opponentBoard->drawBoard(1, 10);
        gameViewer->display(300,200,text);
        gameViewer->display(300,100,message);
    }

private:
    std::string text = "";
    std::string message = "";
    GameState turn;
    GameViewer* gameViewer;
    GameModel* gameModel;
    Board* playerBoard;
    Board* opponentBoard;
    OnlineGameController* onlineGameController;
};


#endif //UNTITLED_GAMECONTROLLER_H
