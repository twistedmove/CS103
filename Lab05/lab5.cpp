#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

unsigned char image[SIZE][SIZE];

// Prototypes
void draw_rectangle(int top, int left, int height, int width);
void draw_ellipse(int cy, int cx, int height, int width);

int main()
{
  int choice;

  // initialize the image to all white pixels
  for(int i=0; i < SIZE; i++){
    for(int j=0; j < SIZE; j++){
      image[i][j] = 255;
    }
  }

  // Do while loop continually accepts user options until 2 is entered
  do
  {
    cout << "To draw a rectangle enter 0. To draw an ellipse enter 1." << endl;
    cout << "To save your drawing as \"output.bmp\" and quit, enter 2." << endl;
    cout << "Option number: ";
    cin >> choice;

    // If 0 is entered asks for rectangle parameters and draws with them
    if (choice == 0)
    {
      int top, left, height, width;

      cout << "Enter the top row, left column, height, and width in that order: ";
      cin >> top >> left >> height >> width;

      draw_rectangle(top, left, height, width);
    }

    // If 1 is entered asks for ellipse parameters and draws with them
    if (choice == 1)
    {
      int cy, cx, height, width;

      cout << "Enter the center row, center column, height, and width in that order: ";
      cin >> cy >> cx >> height >> width;

      draw_ellipse(cy, cx, height, width);
    }
  } while (choice != 2);


  // Writes the resulting image to the .bmp file
  writeGSBMP("output.bmp", image);

  return 0;
}

void draw_rectangle(int top, int left, int height, int width)
{
  // Loops through each row
  for (int i = top; i < top + height; i++)
  {
    // Only operates on row if it is within the array grid
    if (i >= 0 && i < SIZE)
    {
      // Loops through all columns on the first and last row
      if (i == top || i == top + height - 1)
      {
        for (int j = left; j < left + width; j++)
        {
          // Only operates on columns in the array grid
          if (j >= 0 && j < SIZE)
            image[i][j] = 0;
        }
      }  
      // Handles all rows between the first and last
      // Only operates on first and last column when in the array grid 
      else
      {
        if (left >= 0)
          image[i][left] = 0;
        if (left + width - 1 < SIZE)
          image[i][left + width - 1] = 0;
      }
    }
  }
}

void draw_ellipse(int cy, int cx, int height, int width)
{
  // Draws an ellipse using polar coordinates
  for(double theta = 0; theta < 2 * M_PI; theta += 0.01)
  {
    double x = width/2.0 * cos(theta), y = height/2.0 * sin(theta);
    x += cx;
    y += cy;
    // Only draws the circle when it is in the array grid
    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE)
      image[(int)y][(int)x] = 0;
  }
}
