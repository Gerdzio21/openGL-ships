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
                    if (appModel->isGameReady()) {
                        if (key == 13) { //ENTER
                            selectGameConnectionType();
                            appModel->setLocalPlayerBoard();
                        }
                    } else {
                        appModel->getSceneController()->handleKeyPress(key, x, y);
                    }
                    break;
                case AppState::GAME:
                    appModel->getSceneController()->handleKeyPress(key, x, y);
                    break;
            }
        }
    }
    void restartApp() {
        appModel->changeAppState(AppState::MENU);
//        delete boardConfiguratorController;
//        boardConfiguratorController = new BoardConfiguratorController();
        appModel->changeAppState(AppState::WELCOME_SCREEN);
    }

    void startBoardInitialization() {
        appModel->changeAppState(AppState::BOARD_INIT);
    }

    void newGame() {
        appModel->newGame();
    }

    void joinGame() {
        appModel->joinGame();
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
        } else if (appModel->getAppState() == AppState::GAME || appModel->getAppState() == AppState::MENU || appModel->getAppState() == AppState::BOARD_INIT) {
            appModel->getSceneViewer()->displayScene();
        } else {
            appViewer->display();
        }
        glutSwapBuffers();
    }

    BoardConfiguratorController* boardConfiguratorController;
    AppViewer* appViewer;
    AppModel* appModel;
};


#endif //UNTITLED_APPCONTROLLER_H
