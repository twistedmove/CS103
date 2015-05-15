#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void printHistogram(int counts[]);

int roll();

/*Useless main used to test roll()
int main()
{
  srand(time(0));
  for (int i=0;i<10;i++)
  {
    int result = roll();
    cout << result << endl;
  }
  return 0;
}*/

/*Useless main used to test printHistogram()
int main()
{
  int testcounts[100];
  for (int i=0; i<100; i++)
  {
    testcounts[i] = i/2;
  }
  printHistogram(testcounts);
  return 0;
}*/

int main()
{
  //4 dice sum between 4 and 24 inclusive, which is 21 possible values for the array
  int n, rollCount[21] = {0};

  cout << "How many times do you want to roll 4 dice? ";
  cin >> n;

  //Seeds rand() with time(0) for use with roll()
  srand(time(0));

  cout << "Random number: " << roll() << endl;

  for (int i=0; i<n; i++)
  {
    //Finds the sum of 4 dice rolls
    int totalRoll = roll() + roll() + roll() + roll();
    //Adds 1 to the number of times totalRoll was obtained
    rollCount[totalRoll-4]++;
  }

  printHistogram(rollCount);

  return 0;
}

/*Prints labelled lines 4 to 24 with X's to represent how many of that value there are per line
Input an array of int's
No output
Array of int's should store values between 4 and 24, inclusive*/
void printHistogram(int counts[])
{
  //Prints and labels each row
  for (int r=4; r<=24; r++)
  {
    cout << r << ":";
    
    //Fills in the row with X's for how many times r was rolled
    for (int i=0; i<counts[r-4]; i++)
    {
      cout << "X";
    }

    cout << endl;
  }
}

/*Provides the value of 1 dice roll
No input
Outputs an int between 1 and 6 inclusive
Requires cstdlib and ctime libraries and rand() to be seeded*/
int roll()
{
  return rand() % 6 + 1;
}
