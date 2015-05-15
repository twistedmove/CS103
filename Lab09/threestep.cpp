#include "bmplib3.h"
#include "turtle.h"

int main() {
   Turtle leonardo(SIZE/2, SIZE/2, 0); 
   leonardo.move(100);
   leonardo.turn(90);
   leonardo.move(100);
   leonardo.turn(120); // direction is now 0+90+120 = 210
   leonardo.move(200); 
   std_show();
   return 0;
}
