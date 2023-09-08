//
// Created by Gerdzio21 on 2023-09-08.
//
#include "ShipContainerViewer.h"

void ShipContainerViewer::drawContainer(std::vector<Ship *> ships, int selectedShipIndex) {
    drawOnPosition(-5, -5);
    int x = -10;
    int y = 1;
    if (!ships.empty()) {
        Ship* previousShip = ships[0];
        for (auto ship: ships) {
            if (previousShip != ship) {
                if (x + previousShip->getLength() + ship->getLength() < 11) {
                    x = x + previousShip->getLength() + 1;
                } else {
                    x = -10;
                    y = y + 2;
                }
            }
            if (ship == ships[selectedShipIndex]) {
                ship->drawShipOutline(x, y, ShipOrientation::Horizontal);
            } else {
                ship->drawShip(x, y, ShipOrientation::Horizontal);
            }
            previousShip = ship;
        }
    }
}

void ShipContainerViewer::drawOnPosition(int x, int y) {
    float width = 10;
    float height = 5;
    glColor3f(0.0f, 0.0f, 0.0f); // Red color for occupied field
    // ... other cases for different statuses

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x, y + height);
    glVertex2f(x + width, y + height);
    glVertex2f(x + width, y);
    glEnd();
}
