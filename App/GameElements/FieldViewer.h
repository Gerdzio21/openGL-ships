//
// Created by gerdzio21 on 13.08.2023.
//

#ifndef UNTITLED_FIELDVIEWER_H
#define UNTITLED_FIELDVIEWER_H

#include <GL/freeglut.h>
#include <cmath>
#include "Field.h"

class FieldViewer {
public:
    static void drawField(int row, int col, FieldStatus status);
private:
    static void drawX(int col, int row, GLfloat R, GLfloat G, GLfloat B);
    static void drawDot(int col, int row, GLfloat R, GLfloat G, GLfloat B);
    static void drawSquare(int col, int row, GLfloat R, GLfloat G, GLfloat B);
    static void drawSquareOutline(int col, int row, GLfloat R, GLfloat G, GLfloat B);
};


#endif //UNTITLED_FIELDVIEWER_H
