#include "GameViewer.h"

//
// Created by Gerdzio21 on 2023-09-09.
//
GameViewer::GameViewer(GameModel *gameModelPtr) {
    gameModel = gameModelPtr;
    boardViewer = new BoardViewer();
}

void GameViewer::displayScene() {
    boardViewer->drawBoard(-10, 10, gameModel->getLocalPlayerBoard()->getBoardAsVector());
    boardViewer->drawBoard(1, 10, gameModel->getOpponentBoard()->getBoardAsVector());
    display(300, 200, gameModel->getText());
    display(300, 100, gameModel->getMessage());
}

void GameViewer::drawText(int x, int y, const std::string &text) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600); // Współrzędne okna
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    int textWidth = 0;
    for (char c: text) {
        textWidth += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, c);
    }
    int xOffset = x - textWidth / 2;
    glRasterPos2i(xOffset, y);
    for (char c: text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

void GameViewer::display(int x, int y, std::string text) {
    glColor3f(1.0f, 0.0f, 1.0f);
    drawText(x, y, text);
}
