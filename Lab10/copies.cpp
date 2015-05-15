#include "bigint.h"
using namespace std;

int main() {
   BigInt A("15");
   BigInt B(A);
   BigInt C = A;
   A.add(B);
   A.println();
   B.println();
   C.println();
}
