#include <iostream>
#include <cmath>

using namespace std;

int main()
{
  int userNum, positionCounter = 1;

  // Receives integer to be examined from user
  cout << "Enter an integer to find the digits of: ";
  cin >> userNum;

  // Formatting for space between input and output
  cout << endl;

  // Makes negative ints work with this code
  userNum = abs(userNum);

  // Loop runs continues as long as the number to be 
  // examined is not reduced to 0
  while (userNum > 0)
  {
    // Outputs the discovered digit
    cout << positionCounter << "'s digit is " << userNum % 10 << endl;

    // These condition statements are needed to track
    // the digit position because 1*10 is always 1
    if (positionCounter == 1)
    {
      positionCounter = 10;
    }
    else
    {
      positionCounter = positionCounter * 10;
    }

    // Reduces the user's integer to move up a digit and eventually
    // end the loop
    userNum = userNum / 10;
  }

  return 0;
}
