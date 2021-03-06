
#include "util.h"
#include "piece.h"
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
#include <functional>
using namespace std;

float BLOCK_SIZE = 1;
float OUTLINE_WIDTH = BLOCK_SIZE / 7;

float I_COLOR[] = {42.0/255,  239.0/255, 239.0/255}; // 2AEFEF
float J_COLOR[] = {8.0/255,   33.0/255,  237.0/255}; // 0821ED
float L_COLOR[] = {238.0/255, 160.0/255, 38.0/255};  // EEA026
float O_COLOR[] = {239.0/255, 238.0/255, 52.0/255};  // EFEE34
float S_COLOR[] = {39.0/255,  238.0/255, 43.0/255};  // 27EE2B
float T_COLOR[] = {159.0/255, 35.0/255,  237.0/255}; // 9F23ED
float Z_COLOR[] = {237.0/255, 11.0/255,  25.0/255};  // ED0B19

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


void drawPiece(char type, float x, float y, int rotation) {
    /* draws a Tetris peice of specified type at x,y.
        x,y is the bottom left of the shape
        type is one of {i, j, l, o, s, t, z}
        rotation is a positive integer mod 4 indicating the number of
            counter-clockwise rotations from neutral
    */

    float rotateX, rotateY; // position to rotate around
    function<void (int, int)> draw;

    switch(type) {
        case 'i':
            draw = drawI;
            rotateX = x + 1.5;
            rotateY = y + 0.5;
            break;

        case 'o':
            draw = drawO;
            rotateX = x + 1;
            rotateY = y + 1;
            break;
        
        case 'j':
            draw = drawJ;
            rotateX = x + 1.5;
            rotateY = y + 0.5;
            break;
        case 'l':
            draw = drawL;
            rotateX = x + 1.5;
            rotateY = y + 0.5;
            break;
        case 's':
            draw = drawS;
            rotateX = x + 1.5;
            rotateY = y + 0.5;
            break;
        case 't':
            draw = drawT;
            rotateX = x + 1.5;
            rotateY = y + 0.5;
            break;
        case 'z':
            draw = drawZ;
            rotateX = x + 1.5;
            rotateY = y + 0.5;
            break;
        
        default:
            printf("invalid piece \"%c\"\n", type);
            throw "Invalid piece";
    };

    glPushMatrix();
    glTranslatef(rotateX, rotateY, 0.0);
    glRotatef(-90.0*rotation, 0, 0, 1);
    glTranslatef(-rotateX, -rotateY, 0.0);
    draw(x, y);
    glPopMatrix();

}

// TODO make these into objects
void getDimensions(char piece, int rotation, int dims[]) {
   /* returns width, hieght of piece */
   switch (piece) {
      case 'i':
        dims[0] = 4;
        dims[1] = 1;
        break;
         
      case 'o':
        dims[0] = 2;
        dims[1] = 2;
        break;
   
      case 'j':
      case 'l':
      case 's':
      case 't':
      case 'z':
        dims[0] = 3;
        dims[1] = 2;
        break;
   
      default:
         throw "invalid piece";
   }
}

bool withinBounds(Piece p, int grid_width, int grid_height) {
    int minX, minY, maxX, maxY;

    switch (p.type) {
        case 'i':
            switch (p.rotation) {
                case 0:
                    minX = p.x;
                    minY = p.y;
                    maxX = p.x + 4;
                    maxY = p.y + 1;
                    break;
                
                case 1:
                    minX = p.x + 1;
                    minY = p.y - 1;
                    maxX = p.x + 2;
                    maxY = p.y + 2;
                    break;
                
                case 2:
                    minX = p.x - 1;
                    minY = p.y;
                    maxX = p.x + 3;
                    maxY = p.y + 1;
                    break;
                
                case 3:
                    minX = p.x + 1;
                    minY = p.y - 2;
                    maxX = p.x + 2;
                    maxY = p.y + 1;
                    break;
                
                default:
                    throw "invalid rotation";
            }
            break;
            
        case 'o':
            minX = p.x;
            minY = p.y;
            maxX = p.x + 2;
            maxY = p.y + 2;
            break;

        case 'j':
        case 'l':
        case 's':
        case 't':
        case 'z':
            switch (p.rotation) {
                case 0:
                    minX = p.x;
                    minY = p.y;
                    maxX = p.x + 3;
                    maxY = p.y + 2;
                    break;
                
                case 1:
                    minX = p.x + 1;
                    minY = p.y - 1;
                    maxX = p.x + 3;
                    maxY = p.y + 2;
                    break;
                
                case 2:
                    minX = p.x;
                    minY = p.y - 1;
                    maxX = p.x + 3;
                    maxY = p.y + 1;
                    break;
                
                case 3:
                    minX = p.x;
                    minY = p.y - 1;
                    maxX = p.x + 2;
                    maxY = p.y + 2;
                    break;
                
                default:
                    throw "invalid rotation";

            }
            break;

        default:
            throw "invalid piece";
    }

    return minX >= 0 && minY >= 0 && maxX <= grid_width && maxY <= grid_height;

    // return true;
}