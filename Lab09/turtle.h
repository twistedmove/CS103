#ifndef TURTLE_H
#define TURTLE_H

#include "bmplib3.h"

using namespace std;

class Turtle
{
  public:
  // Constructor
    // Turtles begin visible with white lines
    Turtle(double iRow, double iCol, double iDir);

  // Mutators
    // After moving turtles have drawn a line and face the same direction
    void move(double dist);
    void off();
    void on();
    void setColor(color c);
    void turn(double deg);

  private:
    double row, col, dir;
    color linColor;
    bool visible;
};
#endif
