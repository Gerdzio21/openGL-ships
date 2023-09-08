//
// Created by Gerdzio21 on 2023-09-08.
//
#include "FieldViewer.h"

void FieldViewer::drawField(int row, int col, FieldStatus status) {
    switch (status) {
        case OccupiedByShip:
            drawSquare(col,row,0.78f, 0.745f, 0.2137f);
            break;
        case Hit:
            drawX(col,row,1.0f,0.0f,0.0f);
            drawSquareOutline(col,row,0.0f,1.0f,0.0f);
            break;
        case Missed:
            drawDot(col,row,0.0f,0.0f,1.0f);
            drawSquareOutline(col,row,0.0f,1.0f,0.0f);
            break;
        default: //Free or SurroundsShip:
            drawSquareOutline(col,row,0.0f,1.0f,0.0f);
            break;
    }
}

void FieldViewer::drawX(int col, int row, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(col/11.0, -row/11.0);
    glVertex2f((col + 1)/11.0, -(row+1)/11.0 );
    glEnd();

    glBegin(GL_LINES);
    glVertex2f((col + 1)/11.0 , -row/11.0);
    glVertex2f(col/11.0, -(row+1)/11.0);
    glEnd();
}

void FieldViewer::drawDot(int col, int row, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);
    glBegin(GL_QUADS);
    glVertex2f((col+0.25)/11.0, -(row+0.25)/11.0);
    glVertex2f((col-0.25 + 1)/11.0, -(row+0.25)/11.0);
    glVertex2f((col-0.25 + 1)/11.0, -(row-0.25 + 1)/11.0);
    glVertex2f((col+0.25)/11.0, -(row-0.25 + 1)/11.0);
    glEnd();
}

void FieldViewer::drawSquare(int col, int row, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);
    glBegin(GL_QUADS);
    glVertex2f(col/11.0, -row/11.0);
    glVertex2f((col + 1)/11.0, -row/11.0);
    glVertex2f((col + 1)/11.0, -(row + 1)/11.0);
    glVertex2f((col)/11.0, -(row + 1)/11.0);
    glEnd();
}

void FieldViewer::drawSquareOutline(int col, int row, GLfloat R, GLfloat G, GLfloat B) {

    glColor3f(R, G, B);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(col/11.0, -row/11.0);
    glVertex2f((col + 1)/11.0, -row/11.0);
    glVertex2f((col + 1)/11.0, -(row + 1)/11.0);
    glVertex2f((col)/11.0, -(row + 1)/11.0);
    glEnd();
}
