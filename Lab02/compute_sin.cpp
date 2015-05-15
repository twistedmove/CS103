#include <iostream>
#include <cmath>

using namespace std;

// Declaration (function prototype for fact)
int fact(int);

int main(int argc, char *argv[])
{
  // Declare any other variables you need here
  // and/or delete the integer declared below 
  double radians, sinApprox;
  
  // Prompt the user
  cout << "Enter x in radians:  ";
  
  // get input
  cin >> radians;

  // Do some operations
  sinApprox = radians - pow(radians, 3)/fact(3) 
               + pow(radians, 5)/fact(5) - pow(radians, 7)/fact(7);

  // Print the result to the user
  cout << "Sin of " << radians << " radians is approximately "
          << sinApprox << endl;
  
  // You're done
  return 0;
}


int fact(int n)
{
  int i;
  int result=1;
  for(i=1; i <= n; i++){
    result = result * i;
  }
  return result;
}

