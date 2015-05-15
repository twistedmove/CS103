#include "bigint.h"
#include <iostream>

using namespace std;

int main()
{
  BigInt secret("42");
  cout << secret.digits[0] << endl;

  return 0;
}
