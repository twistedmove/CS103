#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

unsigned char image[SIZE][SIZE];

int main()
{
  for(int i=0; i < SIZE; i++){
    for(int j=0; j < SIZE; j++){
      image[i][j] = 255;
    }
  }
  for(int i=0; i < SIZE; i++){
    image[i][128] = 0;
    image[128][i] = 0;
    // every 20 steps, display
    if (i%20==0) showGSBMP(image);
  }
  double r = 50;
  int iters = 0;
  for(double theta=0.0; theta < 2*M_PI; theta += .01){
    int x = r*cos(theta);
    int y = r*sin(theta);
    x += SIZE/2;
    y += SIZE/2;
    image[y][x] = 0;
    // every 20 steps, display
    iters++; 
    if (iters%20==0) showGSBMP(image);
  }

  // at end, display complete image
  showGSBMP(image);

  // save to file
  writeGSBMP("cross.bmp", image);
  return 0;
}
