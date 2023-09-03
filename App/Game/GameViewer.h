//
// Created by gerdzio21 on 05.08.2023.
//

#ifndef UNTITLED_GAMEVIEWER_H
#define UNTITLED_GAMEVIEWER_H


#include "GameModel.h"

class GameViewer {

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

    void display(int x, int y, std::string text) {
        glColor3f(1.0f, 0.0f, 1.0f);
        drawText(x, y, text);
    }
};


#endif //UNTITLED_GAMEVIEWER_H
