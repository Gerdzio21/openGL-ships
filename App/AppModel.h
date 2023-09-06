//
// Created by gerdzio21 on 06.08.2023.
//

#ifndef UNTITLED_APPMODEL_H
#define UNTITLED_APPMODEL_H


#include "Menu/MenuViewer.h"
#include "GameElements/Board.h"
#include "Game/GameModel.h"
#include "SceneController.h"
#include "Game/GameController.h"
#include "BoardConfigurator/BoardConfiguratorModel.h"
#include "BoardConfigurator/BoardConfiguratorController.h"

enum class AppState {
    MENU,
    BOARD_INIT,
    GAME,
    WELCOME_SCREEN

};

class AppModel {

public:
    AppModel(){
        appState = AppState::WELCOME_SCREEN;
    }
    AppState getAppState(){
        return appState;
    }

    void changeAppState(AppState newAppState) {
        switch (newAppState) {
            case AppState::MENU:
                currentSceneController = nullptr;
                currentSceneViewer = new MenuViewer();
                break;
            case AppState::BOARD_INIT:
                boardConfiguratorModel = new BoardConfiguratorModel();
                boardConfiguratorController = new BoardConfiguratorController(boardConfiguratorModel);
                boardConfiguratorViewer = new BoardConfiguratorViewer(boardConfiguratorModel);
                currentSceneViewer = boardConfiguratorViewer;
                currentSceneController = boardConfiguratorController;
                break;
            case AppState::GAME:
                gameModel = new GameModel(localPlayerBoard);
                gameController = new GameController(gameModel);
                gameViewer = new GameViewer(gameModel);
                currentSceneViewer = gameViewer;
                currentSceneController = gameController;
                break;
        }
        appState = newAppState;
    }


    SceneController* getSceneController(){
        return currentSceneController;
    }

    SceneViewer* getSceneViewer(){
        return currentSceneViewer;
    }
    bool isGameReady(){
        return boardConfiguratorModel->isBoardReady();
    }

    void setLocalPlayerBoard() {
        localPlayerBoard = boardConfiguratorModel->getBoard();
    }

    void newGame() {
        changeAppState(AppState::GAME);
        gameController->createGame();
    }

    void joinGame() {
        changeAppState(AppState::GAME);
        gameController->joinGame();
    }

private:
    AppState appState;
    Board* localPlayerBoard;
    SceneViewer* currentSceneViewer;
    SceneController* currentSceneController;

    GameModel* gameModel;
    GameViewer* gameViewer;
    GameController* gameController;

    BoardConfiguratorModel* boardConfiguratorModel;
    BoardConfiguratorViewer* boardConfiguratorViewer;
    BoardConfiguratorController* boardConfiguratorController;


};


#endif //UNTITLED_APPMODEL_H
