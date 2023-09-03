////
//// Created by gerdzio21 on 23.08.2023.
////
//
//#ifndef UNTITLED_MESSAGEVIEWER_H
//#define UNTITLED_MESSAGEVIEWER_H
//
//
//#include <string>
//#include <GL/freeglut.h>
//
//class MessageViewer {
//public:
//    static void displayMessage(int x, int y, const std::string& text) {
//        glMatrixMode(GL_PROJECTION);
//        glPushMatrix();
//        glLoadIdentity();
//        gluOrtho2D(0, 600, 0, 600); // Współrzędne okna
//        glMatrixMode(GL_MODELVIEW);
//        glPushMatrix();
//        glLoadIdentity();
//        int textWidth = 0;
//        for (char c : text) {
//            textWidth += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, c);
//        }
//        int xOffset = x - textWidth / 2;
//        glRasterPos2i(xOffset, y);
//        for (char c : text) {
//            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
//        }
//        glMatrixMode(GL_MODELVIEW);
//        glPopMatrix();
//        glMatrixMode(GL_PROJECTION);
//        glPopMatrix();
//    }
//};
//
//
//#endif //UNTITLED_MESSAGEVIEWER_H
