#include <iostream>

using namespace std;

int main()
{
  // Declaration of variables
  int userNum, oneDigit, tenDigit, hundredDigit;

  // Receives integer to be examined from user
  cout << "Enter an integer between 0 and 999: ";
  cin >> userNum;

  oneDigit = userNum % 10;
  userNum = userNum / 10;

  tenDigit = userNum % 10;
  
  // Mod operator not needed here because 100's digit is expected last
  hundredDigit = userNum / 10;

  // Outputs found results
  cout << "1's digit is " << oneDigit << endl
       << "10's digit is " << tenDigit << endl
       << "100's digit is " << hundredDigit << endl;

  return 0;
}
