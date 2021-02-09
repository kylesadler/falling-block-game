
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
#include <iostream>
using namespace std;

void drawRect(float minX, float minY, float maxX, float maxY, float red, float green, float blue) {
    /* draws a quadrilateral at the given location with given RGB color
    */

    glBegin(GL_POLYGON);
    glColor3f(red, green, blue);
    glVertex2f(minX, minY);
    glVertex2f(minX, maxY);
    glVertex2f(maxX, maxY);
    glVertex2f(maxX, minY);
    glEnd();

}
