#include "ShipViewer.h"

//
// Created by Gerdzio21 on 2023-09-09.
//
void ShipViewer::drawShip(int col, int row, int shipLength, ShipOrientation orientation) {
    if (orientation == ShipOrientation::Horizontal) {
        for (int i = col; i < col + shipLength; i++) {
            drawSector(i, row, orientation);
        }
    } else {
        for (int i = row; i < row + shipLength; i++) {
            drawSector(col, i, orientation);
        }
    }
}

void
ShipViewer::drawShip(int col, int row, int shipLength, ShipOrientation orientation, GLfloat R, GLfloat G, GLfloat B) {
    if (orientation == ShipOrientation::Horizontal) {
        for (int i = col; i < col + shipLength; i++) {
            drawSector(i, row, orientation, R, G, B);
        }
    } else {
        for (int i = row; i < row + shipLength; i++) {
            drawSector(col, i, orientation, R, G, B);
        }
    }
}

void ShipViewer::drawSector(int col, int row, ShipOrientation orientation) {
    drawSector(col, row, orientation, 0.78f, 0.745f, 0.2137f);
}

void ShipViewer::drawSector(int col, int row, ShipOrientation orientation, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);
    glBegin(GL_QUADS);
    glVertex2f(col / 11.0, -row / 11.0);
    glVertex2f((col + 1) / 11.0, -row / 11.0);
    glVertex2f((col + 1) / 11.0, -(row + 1) / 11.0);
    glVertex2f((col) / 11.0, -(row + 1) / 11.0);
    glEnd();
}

void ShipViewer::drawShipOutline(int x, int y, int length, ShipOrientation shipOrientation) {
    glColor3f(1.00f, 0.00f, 0.00f);
    glBegin(GL_QUADS);
    if (shipOrientation == ShipOrientation::Horizontal) {
        glVertex2f(x / 11.0, -y / 11.0);
        glVertex2f((x + length) / 11.0, -y / 11.0);
        glVertex2f((x + length) / 11.0, -(y + 1) / 11.0);
        glVertex2f((x) / 11.0, -(y + 1) / 11.0);
    } else if (shipOrientation == ShipOrientation::Vertical) {
        glVertex2f(x / 11.0, -y / 11.0);
        glVertex2f((x + 1) / 11.0, -y / 11.0);
        glVertex2f((x + 1) / 11.0, -(y + length) / 11.0);
        glVertex2f((x) / 11.0, -(y + length) / 11.0);
    }
    glEnd();
}
