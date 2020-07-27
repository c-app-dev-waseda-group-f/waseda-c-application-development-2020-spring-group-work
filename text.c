#include <GL/glut.h>
#include "text.h"

void drawText(const char* text, double x, double y, double windowHeight, double windowWidth) {

    glDisable(GL_LIGHTING);
    glColor3f(0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    glScalef(1, -1, 1);
    glTranslatef(0, -windowHeight, 0);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glLoadIdentity();

    glRasterPos2f(x, y);

    for (const char* c = text; *c != '\0'; c++) {

        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
}