//
// Created by gerdzio21 on 09.08.2023.
//

#ifndef UNTITLED_MENUVIEWER_H
#define UNTITLED_MENUVIEWER_H


#include <iostream>
#include <stdlib.h>
#include "../../Screen.h"
#include "../SceneViewer.h"
#include <GL/freeglut.h>

class MenuViewer: public SceneViewer{
public:
    MenuViewer() = default;
    virtual void displayScene();
    void drawText(int x, int y, const std::string& text);


};


#endif //UNTITLED_MENUVIEWER_H
