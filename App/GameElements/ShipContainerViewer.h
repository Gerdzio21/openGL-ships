//
// Created by gerdzio21 on 15.08.2023.
//

#ifndef UNTITLED_SHIPCONTAINERVIEWER_H
#define UNTITLED_SHIPCONTAINERVIEWER_H

#include <GL/freeglut.h>
class ShipContainerViewer {
public:
    void drawContainer(int x, int y) {
        float width = 10;
        float height =5;
        glColor3f(0.0f, 0.0f, 0.0f); // Red color for occupied field
        // ... other cases for different statuses

        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x, y+height);
        glVertex2f(x+width, y+height);
        glVertex2f(x+width, y);
        glEnd();
    }
};


#endif //UNTITLED_SHIPCONTAINERVIEWER_H
