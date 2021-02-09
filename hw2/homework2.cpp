
#include "util.h"
#include "piece.h" // PIECES are 1 unit wide
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


//---------------------------------------
// Display constants
//---------------------------------------

float GRID_WIDTH = 10;
float GRID_HEIGHT = 20;
float SCREEN_PADDING = 1;
float BORDER_COLOR[] = {100.0/255, 100.0/255, 100.0/255};
float GRID_COLOR[] = {200.0/255, 200.0/255, 200.0/255};

const int PIECE_LIMIT = (int) (GRID_WIDTH*GRID_HEIGHT/4) + 1;
int NUM_PIECES = 0;
Piece PIECES[50]; // arrange these in a grid-like datastructure to make collision detection easier

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(
      -SCREEN_PADDING, GRID_WIDTH+SCREEN_PADDING,
      -SCREEN_PADDING, GRID_HEIGHT+SCREEN_PADDING,
      0.0, 1.0
   );
}

void addPiece(char type, int x, int y) {
   if (NUM_PIECES < PIECE_LIMIT) {
      Piece p = {type, x, y, 0, false};
      PIECES[NUM_PIECES++] = p;
   }
}

void rotatePiece() {
   /* rotates current piece 90 degrees counter clockwise  */
   if (NUM_PIECES == 0) {
      return;
   }
   Piece p = PIECES[NUM_PIECES-1];
   if (p.frozen) {
      return;
   }
   p.rotation = (p.rotation + 1) % 4;
   if (withinBounds(p, GRID_WIDTH, GRID_HEIGHT)){
      PIECES[NUM_PIECES-1] = p;
   }
}

void freezePiece() {
   /* freezes current piece */
   if (NUM_PIECES == 0) {
      return;
   }
   Piece p = PIECES[NUM_PIECES-1];
   p.frozen = true;
   PIECES[NUM_PIECES-1] = p;
}

void movePiece(char direction) {
   /* moves current piece in specified direction
      direction is one of {l, r, d}
   */
   if (NUM_PIECES == 0) {
      return;
   }

   // printf("moving %c\n", direction);

   int index = NUM_PIECES-1;
   Piece p = PIECES[index];

   if (p.frozen) {
      return;
   }

   switch (direction) {
      case 'l':
         p.x -= 1;
         break;
      
      case 'r':
         p.x += 1;
         break;
      
      case 'd':
         p.y -= 1;
         break;
      
      default:
         break;
   }
   
   if (withinBounds(p, GRID_WIDTH, GRID_HEIGHT)){
      PIECES[index] = p;
   }

}

double getRandomPosition() {
    // generate a random starting x position for Tetris piece
    return rand() % (int) (GRID_WIDTH - 4); // make room for tetris peice
}

void drawBorder() {
   drawRect(
      -SCREEN_PADDING, -SCREEN_PADDING, GRID_WIDTH, 0,
      BORDER_COLOR[0], BORDER_COLOR[1], BORDER_COLOR[2]
      );
   drawRect(
      GRID_WIDTH, -SCREEN_PADDING, GRID_WIDTH+SCREEN_PADDING, GRID_HEIGHT,
      BORDER_COLOR[0], BORDER_COLOR[1], BORDER_COLOR[2]
      );
   drawRect(
      0, GRID_HEIGHT, GRID_WIDTH+SCREEN_PADDING, GRID_HEIGHT+SCREEN_PADDING,
      BORDER_COLOR[0], BORDER_COLOR[1], BORDER_COLOR[2]
      );
   drawRect(
      -SCREEN_PADDING, 0, 0, GRID_HEIGHT+SCREEN_PADDING,
      BORDER_COLOR[0], BORDER_COLOR[1], BORDER_COLOR[2]
      );
}

void drawGrid() {
   glBegin(GL_LINES);
   glColor3f(GRID_COLOR[0], GRID_COLOR[1], GRID_COLOR[2]);
   for (int y = 0; y <= GRID_HEIGHT; y++) {
      glVertex2f(-SCREEN_PADDING, y); 
      glVertex2f(GRID_WIDTH+SCREEN_PADDING, y); 
   }
   for (int x = 0; x <= GRID_WIDTH; x++) {
      glVertex2f(x, -SCREEN_PADDING); 
      glVertex2f(x, GRID_HEIGHT+SCREEN_PADDING); 
   }
   glEnd();
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   
   drawBorder();
   drawGrid();

   if (NUM_PIECES > 0) {
      // printf("about to draw %d pieces!\n", NUM_PIECES);

      for (int i = 0; i < NUM_PIECES; i++) {
         Piece p = PIECES[i];
         // printf("%d %d\n", p.x, p.y);
         drawPiece(p.type, p.x, p.y, p.rotation);
      }
   }

   glFlush();
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'i':
      case 'I':
      
      case 'j':
      case 'J':
      
      case 'l':
      case 'L':

      case 'o':
      case 'O':
      
      case 's':
      case 'S':
      
      case 't':
      case 'T':

      case 'z':
      case 'Z':
         addPiece(tolower(key), getRandomPosition(), GRID_HEIGHT-2);
         break;

      case ' ':
         freezePiece();
         break;
      
      default:
         break;
   }

   // Redraw objects
   glutPostRedisplay();
}

//---------------------------------------
// Special callback for OpenGL
//---------------------------------------
void special(int key, int x, int y)
{
   switch(key) {
   case GLUT_KEY_UP:
      rotatePiece();
      break;
   case GLUT_KEY_DOWN:
      movePiece('d');
      break;
   case GLUT_KEY_LEFT:
      movePiece('l');
      break;
   case GLUT_KEY_RIGHT:
      movePiece('r');
      break;
   default:
      break;
   }

   // Redraw objects
   glutPostRedisplay();
}

// ---------------------------------------
// Main program
// ---------------------------------------
int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   int windowWidth = (int)(GRID_WIDTH+SCREEN_PADDING*2)*75;
   int windowHeight = (int)(GRID_HEIGHT+SCREEN_PADDING*2)*75;
   glutInitWindowSize(windowWidth, windowHeight);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutCreateWindow("Tetris");
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(special);
   init();
   glutMainLoop();
   return 0;
}
