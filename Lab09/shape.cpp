#include "turtle.h"
#include "bmplib3.h"
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
   if (argc != 2) {
      cerr << "Usage: shape N\nwhere N is an integer >= 3" << endl;
      return 1;
   }   
   int N = atoi(argv[1]);
   
   Turtle t(SIZE/2, SIZE/2, 0);
   for (int i=0; i<N; i++) {
      t.turn(360.0/N); // do a full turn in N parts
      t.move(360.0/N); // draw a shape with perimeter 360 pixels
   }
   std_show();
   
   if (N<0) { // easter egg
      for (int i=0; i<4; i++) {
         t.turn(135); t.move(50); t.turn(-45); t.move(50);
      }
      std_show();
   }
}
