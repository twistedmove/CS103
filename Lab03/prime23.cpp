#include <iostream>

using namespace std;

int main()
{
  int userNum, twos = 0, threes = 0;

  // Asks for and receives int to be factored from user
  cout << "Type a natural number(1,2,3,etc.) and press return: ";
  cin >> userNum;

  // Gathers factors of 2
  if (userNum % 2 == 0)
  {
    while (userNum % 2 == 0)
    {
      userNum = userNum/2;
      twos++;
    }
  }
  // Gathers factors of 3
  if (userNum % 3 == 0)
  {
    while (userNum % 3 == 0)
    {
      userNum = userNum/3;
      threes++;
    }
  }

  // Case for only 2 and 3 factors, gives how many of each
  if (userNum == 1)
  {
    cout << "Yes, " << twos << " twos and " << threes << " threes." << 		    endl;
  }
  // Case for other factors
  else
  {
    cout << "No." << endl;
  }

  return 0;
}    
