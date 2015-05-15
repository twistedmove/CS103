#include "bigint.h"
using namespace std;

int main() {
   BigInt a("13");
   BigInt b("42");
   b.add(a);    // increase b by a
   b.println(); // prints 55
   b.add(a);    // increase b by a
   b.println(); // prints 68
}
