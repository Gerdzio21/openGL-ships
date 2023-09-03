//
// Created by gerdzio21 on 09.08.2023.
//

#ifndef UNTITLED_MENUCONTROLLER_H
#define UNTITLED_MENUCONTROLLER_H


#include <iostream>
#include "../Event/EventHandler.h"
#include "MenuViewer.h"


class MenuController {

public:
    MenuController(){
        menuViewer = new MenuViewer();
    }
    void showMenu(){
        menuViewer->display();
    }
    MenuViewer* menuViewer;
};


#endif //UNTITLED_MENUCONTROLLER_H
