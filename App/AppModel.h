//
// Created by gerdzio21 on 06.08.2023.
//

#ifndef UNTITLED_APPMODEL_H
#define UNTITLED_APPMODEL_H


#include "Menu/MenuViewer.h"
#include "GameElements/Board.h"

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

                break;
            case AppState::BOARD_INIT:
                break;
            case AppState::GAME:
                break;
        }
        appState = newAppState;
    }


private:
    AppState appState;
};


#endif //UNTITLED_APPMODEL_H
