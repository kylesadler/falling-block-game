#include <stdbool.h>

struct Piece {
   char type;
   int x;
   int y;
   int rotation; // 0 to 3
   bool frozen;
};

void drawPiece(char type, float x, float y, int rotation);

bool withinBounds(Piece p, int grid_width, int grid_height);