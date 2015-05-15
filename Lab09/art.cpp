#include "turtle.h"
#include "bmplib3.h"
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
// Creates 4 turtles in the middle(ish) facing down
  // Creates magenta turtle jim
  Turtle jim(SIZE/2-10, SIZE/2, 0);
  jim.setColor(magenta);
  // Creates white turtle jim
  Turtle tim(SIZE/2, SIZE/2-10, 0);
  tim.setColor(white);
  // Creates cyan turtle jim
  Turtle kim(SIZE/2+10, SIZE/2, 0);
  kim.setColor(cyan);
  // Creates red turtle jim
  Turtle zim(SIZE/2, SIZE/2+10, 0);
  zim.setColor(red);

  // Seeds the RNG
  srand(time(0));

  // An array of distance and turn values for each turtle
  double dist[4], turn[4];

  // Start each turtle facing a random direction
  for(int i = 0; i < 4; i++)
    turn[i] = rand()%360;
  jim.turn(turn[0]);
  tim.turn(turn[1]);
  kim.turn(turn[2]);
  zim.turn(turn[3]);

  // Move the turtles 10 times
  for(int times = 0; times < 11; times++)
  {    
    for(int i = 0; i < 4; i++)
    {
      // A random distance between 30 and 90 
      dist[i] = (rand() % 61) + 30;
      // Turns set to 120 degrees for triangles
      turn[i] = 120;
    }
  
    // Make the moves
    jim.turn(turn[0]);
    jim.move(dist[0]);
    tim.turn(turn[1]);
    tim.move(dist[1]);
    kim.turn(turn[2]);
    kim.move(dist[2]);
    zim.turn(turn[3]);
    zim.move(dist[3]);

  //Draw the art
  std_show();
  }

  return 0;
}
