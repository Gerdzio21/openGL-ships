#include <iostream>
#include <winsock2.h>
#include "App/WebServices/ConnectionManager.h"
#include "App/AppController.h"
#include "App/Event/EventHandler.h"

#include "GL/glut.h"
int windowHeight = 600;
int windowWidth = 600;
AppController& getAppControllerInstance() {
    static AppController instance;
    return instance;
}


AppViewer& getAppViewerInstance() {
    static AppViewer instance;
    return instance;
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    getAppControllerInstance().draw();
}

void reshape(int width, int height) {
    glutReshapeWindow(600, 600);
}

void keyboard(unsigned char key, int x, int y) {
    getAppControllerInstance().handleKeyPress(key, x, y);
}

void update(int value) {
    getAppControllerInstance().update();
    glutTimerFunc(1000 / 60, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Game Window");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);
    getAppControllerInstance().run();
    return 0;
}





//int main(int argc, char** argv)
//{
//    glutInit(&argc, argv);
//    EventHandler eventHandler;
//    AppController appController = AppController(eventHandler,argc, argv);
//    appController.run();
//    return 0;
//}
//int main() {
//    EventHandler eventHandler;
//    AppController* app = new AppController(eventHandler);
//    while(true) {
//        std::string input;
//        std::getline(std::cin, input);
//        Event event;
//        event.type = EventType::KeyPressed;
//        event.key = input[0];
//        eventHandler.notify(event);
//    }
//    return 0;
//}
