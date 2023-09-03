//
// Created by gerdzio21 on 06.08.2023.
//

#ifndef UNTITLED_APPCONTROLLER_H
#define UNTITLED_APPCONTROLLER_H


#include <iostream>
#include "AppViewer.h"
#include "WebServices/ConnectionManager.h"
#include "Event/EventHandler.h"
#include "Menu/MenuController.h"
#include "AppModel.h"
#include "BoardConfigurator/BoardConfiguratorController.h"
#include "Game/GameController.h"


class AppController {
public:

    AppController() {
        appViewer = new AppViewer();
        appModel = new AppModel();
        menuController = new MenuController();
        boardConfiguratorController = new BoardConfiguratorController();
        sceneController = boardConfiguratorController;
        gameController = new GameController();
    }

    void run() {
        glutMainLoop();
    }

    void handleKeyPress(unsigned char key, int x, int y) {
        if (tolower(key) == 'p') {
            restartApp();
        } else {
            switch (appModel->getAppState()) {
                case AppState::WELCOME_SCREEN:
                    if (key == 13) { //ENTER
                        startBoardInitialization();
                    }
                    break;
                case AppState::MENU:
                    if (tolower(key) == 'n') {
                        newGame();
                    }
                    if (tolower(key) == 'j') {
                        joinGame();
                    }
                    break;
                case AppState::BOARD_INIT:
                    if (boardConfiguratorController->isBoardReady()) {
                        if (key == 13) { //ENTER
                            selectGameConnectionType();
                        }
                    } else {
                        sceneController->handleKeyPress(key, x, y);
                    }
                    break;
                case AppState::GAME:
                    sceneController->handleKeyPress(key, x, y);
                    break;
            }
        }
    }
    void restartApp() {
        appModel->changeAppState(AppState::MENU);
        delete boardConfiguratorController;
        delete gameController;
        boardConfiguratorController = new BoardConfiguratorController();
        gameController = new GameController();
        appModel->changeAppState(AppState::WELCOME_SCREEN);
    }

    void startBoardInitialization() {
        appModel->changeAppState(AppState::BOARD_INIT);
        sceneController = boardConfiguratorController;
    }

    void newGame() {
        appModel->changeAppState(AppState::GAME);
        sceneController = gameController;
        gameController->setUserBoard(boardConfiguratorController->getBoard());
        gameController->createGame();
        //gameController->getOpponentMove();
    }

    void joinGame() {
        gameController->setUserBoard(boardConfiguratorController->getBoard());
        sceneController = gameController;
        appModel->changeAppState(AppState::GAME);
        gameController->joinGame();
    }

    void selectGameConnectionType() {
        appModel->changeAppState(AppState::MENU);
    }


    void update() {
        glutPostRedisplay();
    }

    void draw() {
        if (appModel->getAppState() == AppState::WELCOME_SCREEN) {
            appViewer->displayWelcomeScreen();
        } else if (appModel->getAppState() == AppState::MENU) {
            menuController->showMenu();
        } else if (appModel->getAppState() == AppState::BOARD_INIT) {
            boardConfiguratorController->showBoard();
        } else if (appModel->getAppState() == AppState::GAME) {
            gameController->showGame();
        } else {
            appViewer->display();
        }
        glutSwapBuffers();
    }

    BoardConfiguratorController* boardConfiguratorController;
    GameController* gameController;
    AppViewer* appViewer;
    AppModel* appModel;
    MenuController* menuController;
    SceneController* sceneController;
};


#endif //UNTITLED_APPCONTROLLER_H
