#include "bmplib3.h"
#include "turtle.h"

int main() {
   Turtle raphael(10, SIZE/2, 0); 
   raphael.setColor(white);
   raphael.move(100);
   raphael.off(); // ninja vanish
   raphael.move(10);
   raphael.on();  // ninja unvanish
   raphael.move(100);
   raphael.turn(-90);
   raphael.setColor(red);
   raphael.move(50);
   std_show();
   return 0;
}
