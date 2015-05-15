#include "turtle.h"
#include "bmplib3.h"
#include <cmath>

using namespace std;

// Constructor
Turtle::Turtle(double iRow, double iCol, double iDir)
{
  row = iRow;
  col = iCol;
  dir = iDir;
  // Turtles begin as visible
  visible = true;
  // Turtles begin as white
  linColor = white;
}

// Mutators
void Turtle::move(double dist)
{
  // Stores the turtle's future position in temp variables for use with the
  //  std_draw_line function
  double newRow, newCol;
  // Convert direction to radians for use with sin and cos
  newRow = row + (dist * cos(dir * (M_PI/180)));
  newCol = col + (dist * sin(dir * (M_PI/180)));

  // Only draws the turtle's path when it's been set to on
  if(visible)
    std_draw_line(linColor, row, col, newRow, newCol);

  // Updates the turtle's new position
  row = newRow;
  col = newCol;
}

void Turtle::off()
{
  visible = false;
}

void Turtle::on()
{
  visible = true;
}

void Turtle::setColor(color c)
{
  linColor = c;
}

void Turtle::turn(double deg)
{
  dir += deg;
}
