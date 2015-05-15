#include "bigint.h"

using namespace std;

int main()
{
  BigInt a("5");
  BigInt b("499");
  BigInt c("1099");

  a.add(b);
  a.println(); // Prints 504
  c.add(b);
  c.println(); // Prints 1598
  c.add(a);
  c.println(); // Prints 2102

  return 0;
}
  
