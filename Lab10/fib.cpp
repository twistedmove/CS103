#include "bigint.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
   if (argc != 2) {
      cerr << "Usage: fib N\nwhere N is an integer >= 2" << endl;
      return 1;
   }   
   int N = atoi(argv[1]);
   
   BigInt x("1");
   x.println();
   BigInt y("1");
   y.println();
   for (int i=3; i<=N; i++) {
      BigInt tmp = y;
      y.add(x);
      y.println();
      x = tmp;
   }
}
