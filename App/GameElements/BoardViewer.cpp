//
// Created by Gerdzio21 on 2023-09-08.
//
#include "BoardViewer.h"
void BoardViewer::drawBoard(int x, int y, std::vector <std::vector<Field *>> board) {
    GLfloat step = (600 / 22.0f);
    GLfloat xOffset = 300.0f + (x - 1) * step + step / 2 - glutBitmapWidth(GLUT_BITMAP_HELVETICA_12, '1');
    GLfloat yOffset = 600.0f - step / 2;
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            FieldStatus status = board[row][col]->getFieldStatus();
            FieldViewer::drawField(row - y, col + x, status);
        }
    }
    for (int row = 0; row < 10; row++) {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, 600, 0, 600);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glColor3f(1.0f, 1.0f, 1.0f);
        if (row == 9) {
            glRasterPos2f(xOffset,
                          yOffset - step * (row + 1));
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '1');
            float charWidth = glutBitmapWidth(GLUT_BITMAP_HELVETICA_12, '1');
            glRasterPos2f(xOffset + charWidth,
                          yOffset - step * (row + 1));
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '0');
        } else {
            glRasterPos2f(xOffset,
                          yOffset - step * (row + 1));
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (char) row + '1');
        }

        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
    }
    for (int col = 0; col < 10; col++) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, 600, 0, 600); // Współrzędne okna
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glColor3f(1.0f, 1.0f, 1.0f);
        xOffset = 300.0f + (x - 1) * step + step / 2 - glutBitmapWidth(GLUT_BITMAP_HELVETICA_12, (char) col + 'A');
        glRasterPos2f(xOffset + step * (col + 1), yOffset);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (char) col + 'A');
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
    }
}
