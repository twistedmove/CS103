#include <iostream>
#include <cmath>

using namespace std;

int main()
{
  int theta;
  double PI = 3.14159265;

  // Asks for and receives theta from the user
  cout << "Type an int between 15 and 75(included) for angle theta: ";
  cin >> theta;

  // Lines loop
  for (int i = 1; i <= 30; i++)
  {
    // Converts theta to radians to use tangent to relate x to y
    int xLength = i * tan(theta * PI / 180);

    // Restricts xLength to 20 when in the desired range
    if ((xLength <= 30) && (xLength >= 20))
    {
      xLength = 20;
    }

    // *s per line loop
    for (int j = 1; j <= xLength; j++)
    {
      cout << "*";
    }
    // Starts next line
    cout << endl;
  }

return 0;
}
