//
// Created by gerdzio21 on 09.08.2023.
//

#ifndef UNTITLED_MENUVIEWER_H
#define UNTITLED_MENUVIEWER_H


#include <iostream>
#include <stdlib.h>
#include "../../Screen.h"

class MenuViewer{
public:
    void drawText(int x, int y, const std::string& text) {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, 600, 0, 600); // Współrzędne okna
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        int textWidth = 0;
        for (char c : text) {
            textWidth += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, c);
        }
        int xOffset = x - textWidth / 2;
        glRasterPos2i(xOffset, y);
        for (char c : text) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
    }

    void display(){
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Czarne tło
            glClear(GL_COLOR_BUFFER_BIT);
            // Renderowanie menu
            glColor3f(1.0f, 1.0f, 1.0f); // Biały kolor
            drawText(300, 400, "MENU");
            drawText(300, 350, "PRESS N to start new game");
            drawText(300, 300, "PRESS J to join the game");
    }
};


#endif //UNTITLED_MENUVIEWER_H
