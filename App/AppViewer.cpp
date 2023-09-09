#include "AppViewer.h"

//
// Created by Gerdzio21 on 2023-09-09.
//
void AppViewer::drawText(int x, int y, const std::string &text) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);
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

void AppViewer::display() {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 1.0f);
    drawText(400, 300, "SHIPS by Bernard Pokorski");
}

void AppViewer::displayWelcomeScreen() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 1.0f);
    drawText(300, 400, "Press ENTER to start the game!");
    drawText(300, 300, "SHIPS by Bernard Pokorski");
}
