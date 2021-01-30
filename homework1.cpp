#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
using namespace std;


//---------------------------------------
// Display constants
//---------------------------------------
float BLOCK_SIZE = 0.05;
float OUTLINE_WIDTH = BLOCK_SIZE / 7;
float I_COLOR[] = {42.0/255,  239.0/255, 239.0/255}; // 2AEFEF
float J_COLOR[] = {8.0/255,   33.0/255,  237.0/255}; // 0821ED
float L_COLOR[] = {238.0/255, 160.0/255, 38.0/255};  // EEA026
float O_COLOR[] = {239.0/255, 238.0/255, 52.0/255};  // EFEE34
float S_COLOR[] = {39.0/255,  238.0/255, 43.0/255};  // 27EE2B
float T_COLOR[] = {159.0/255, 35.0/255,  237.0/255}; // 9F23ED
float Z_COLOR[] = {237.0/255, 11.0/255,  25.0/255};  // ED0B19


//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
}

double getRandomPosition() {
    // generate a random position between 0 and 1
    int n = 1000000;
    return (rand() % n) / (double)n * (1-BLOCK_SIZE*4); // make room for tetris peice
}

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

void drawBlock(float x, float y, float color[]) {
    /* draws a tetris block at the given x,y location with given RGB color
        x,y indicates bottom left of block
    */
    float red = color[0];
    float green = color[1];
    float blue = color[2];

    float xMax = x + BLOCK_SIZE;
    float yMax = y + BLOCK_SIZE;

    drawRect(x, y, xMax, yMax, red, green, blue);

    // draws outline counter clockwise starting with bottom
    float medRed = red / 1.5;
    float medGreen = green / 1.5;
    float medBlue = blue / 1.5;

    float darkRed = red / 3;
    float darkGreen = green / 3;
    float darkBlue = blue / 3;

    float lightRed = (red + 1)/2;
    float lightGreen = (green + 1)/2;
    float lightBlue = (blue + 1)/2;

    drawRect(
        x + OUTLINE_WIDTH, y, xMax - OUTLINE_WIDTH, y + OUTLINE_WIDTH,
        darkRed, darkGreen, darkBlue
        );
    drawRect(
        xMax - OUTLINE_WIDTH, y + OUTLINE_WIDTH, xMax, yMax - OUTLINE_WIDTH,
        medRed, medGreen, medBlue
        );
    drawRect(
        x + OUTLINE_WIDTH, yMax - OUTLINE_WIDTH, xMax - OUTLINE_WIDTH, yMax,
        lightRed, lightGreen, lightBlue
        );
    drawRect(
        x, y + OUTLINE_WIDTH, x  + OUTLINE_WIDTH, yMax - OUTLINE_WIDTH,
        medRed, medGreen, medBlue
        );

    // draw traingle corners counter clockwise starting at bottom left
    glBegin(GL_TRIANGLES);

    glColor3f(darkRed, darkGreen, darkBlue);
    glVertex2f(x + OUTLINE_WIDTH, y + OUTLINE_WIDTH);
    glVertex2f(x + OUTLINE_WIDTH, y);
    glVertex2f(x, y);

    glColor3f(darkRed, darkGreen, darkBlue);
    glVertex2f(xMax - OUTLINE_WIDTH, y + OUTLINE_WIDTH);
    glVertex2f(xMax - OUTLINE_WIDTH, y);
    glVertex2f(xMax, y);
    
    glColor3f(medRed, medGreen, medBlue);
    glVertex2f(xMax - OUTLINE_WIDTH, y + OUTLINE_WIDTH);
    glVertex2f(xMax, y + OUTLINE_WIDTH);
    glVertex2f(xMax, y);
    
    glColor3f(medRed, medGreen, medBlue);
    glVertex2f(xMax - OUTLINE_WIDTH, yMax - OUTLINE_WIDTH);
    glVertex2f(xMax, yMax - OUTLINE_WIDTH);
    glVertex2f(xMax, yMax);
    

    glColor3f(lightRed, lightGreen, lightBlue);
    glVertex2f(xMax - OUTLINE_WIDTH, yMax - OUTLINE_WIDTH);
    glVertex2f(xMax - OUTLINE_WIDTH, yMax);
    glVertex2f(xMax, yMax);
    
    glColor3f(lightRed, lightGreen, lightBlue);
    glVertex2f(x, yMax);
    glVertex2f(x + OUTLINE_WIDTH, yMax - OUTLINE_WIDTH);
    glVertex2f(x + OUTLINE_WIDTH, yMax);
    
    glColor3f(medRed, medGreen, medBlue);
    glVertex2f(x + OUTLINE_WIDTH, yMax - OUTLINE_WIDTH);
    glVertex2f(x, yMax - OUTLINE_WIDTH);
    glVertex2f(x, yMax);
    
    glColor3f(medRed, medGreen, medBlue);
    glVertex2f(x, y + OUTLINE_WIDTH);
    glVertex2f(x, y);
    glVertex2f(x + OUTLINE_WIDTH, y + OUTLINE_WIDTH);
    
    glEnd();
}


/* 
    Tetris piece drawing functions
*/

void drawI(float x, float y) {
    /* draws the I Tetris peice at x,y.
        x,y is the bottom left of the shape
    */
    for (int i = 0; i < 4; i++){
        drawBlock(x+BLOCK_SIZE*i, y, I_COLOR);
    }

}

void drawJ(float x, float y) {
    /* draws the J Tetris peice at x,y.
        x,y is the bottom left of the shape
    */
    drawBlock(x, y+BLOCK_SIZE, J_COLOR);
    for (int i = 0; i < 3; i++){
        drawBlock(x+BLOCK_SIZE*i, y, J_COLOR);
    }

}

void drawL(float x, float y) {
    /* draws the L Tetris peice at x,y.
        x,y is the bottom left of the shape
    */
    drawBlock(x+BLOCK_SIZE*2, y+BLOCK_SIZE, L_COLOR);
    for (int i = 0; i < 3; i++){
        drawBlock(x+BLOCK_SIZE*i, y, L_COLOR);
    }

}

void drawO(float x, float y) {
    /* draws the O Tetris peice at x,y.
        x,y is the bottom left of the shape
    */
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            drawBlock(x+BLOCK_SIZE*j, y+BLOCK_SIZE*i, O_COLOR);
        }
    }

}

void drawS(float x, float y) {
    /* draws the S Tetris peice at x,y.
        x,y is the bottom left of the shape
    */
    drawBlock(x, y, S_COLOR);
    drawBlock(x+BLOCK_SIZE, y, S_COLOR);
    drawBlock(x+BLOCK_SIZE, y+BLOCK_SIZE, S_COLOR);
    drawBlock(x+BLOCK_SIZE*2, y+BLOCK_SIZE, S_COLOR);

}

void drawT(float x, float y) {
    /* draws the T Tetris peice at x,y.
        x,y is the bottom left of the shape
    */
    drawBlock(x+BLOCK_SIZE, y+BLOCK_SIZE, T_COLOR);
    for (int i = 0; i < 3; i++){
        drawBlock(x+BLOCK_SIZE*i, y, T_COLOR);
    }

}

void drawZ(float x, float y) {
    /* draws the Z Tetris peice at x,y.
        x,y is the bottom left of the shape
    */
    drawBlock(x, y+BLOCK_SIZE, Z_COLOR);
    drawBlock(x+BLOCK_SIZE, y, Z_COLOR);
    drawBlock(x+BLOCK_SIZE, y+BLOCK_SIZE, Z_COLOR);
    drawBlock(x+BLOCK_SIZE*2, y, Z_COLOR);

}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawZ(getRandomPosition(), getRandomPosition());
    drawI(getRandomPosition(), getRandomPosition());
    drawJ(getRandomPosition(), getRandomPosition());
    drawL(getRandomPosition(), getRandomPosition());
    drawO(getRandomPosition(), getRandomPosition());
    drawS(getRandomPosition(), getRandomPosition());
    drawT(getRandomPosition(), getRandomPosition());

    glFlush();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitWindowSize(1500, 1500);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutCreateWindow("Square");
   glutDisplayFunc(display);
   init();
   glutMainLoop();
   return 0;
}
