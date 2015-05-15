#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  // Declaration of variables
  int red, green, blue;
  double white, cyan, magenta, yellow, black;

  // Takes in integer RGB color values from user
  cout << "Enter integer values for red, green, and blue" << endl
       << "in that order and separated by space or enter" << endl;
  cin >> red >> green >> blue;

  // Sets white as the max of red, green, or blue divided by 255
  white = max(red/255., green/255.);
  if (max(green/255., blue/255.) > white)
  {
    white = max(green/255., blue/255.);
  }

  // Converts RGB colors to CMYK
  cyan = (white - red/255.)/white;
  magenta = (white - green/255.)/white;
  yellow = (white  - blue/255.)/white;
  black = 1 - white;

  // Outputs color conversion results
  cout << "Cyan is " << cyan << endl
       << "Magenta is " << magenta << endl
       << "Yellow is " << yellow << endl
       << "Black is " << black << endl;

  return 0;
}
