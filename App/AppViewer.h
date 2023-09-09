//
// Created by gerdzio21 on 06.08.2023.
//

#ifndef UNTITLED_APPVIEWER_H
#define UNTITLED_APPVIEWER_H


#include <iostream>
#include <GL/freeglut.h>
#include "../Screen.h"

class AppViewer {

public:
    void drawText(int x, int y, const std::string& text);

    void display();

    void displayWelcomeScreen();
};

#endif //UNTITLED_APPVIEWER_H
