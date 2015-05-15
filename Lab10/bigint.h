#ifndef BIGINT_H
#define BIGINT_H

#include <string>
#include <vector>

using namespace std;

class BigInt {
  public:
   // Constructors
    // Convert string to BigInt, base defaults to 10
    // Assumes only valid characters are part of string
    BigInt(string s);
    // Convert string to BigInt with base nBase
    // Assumes nBase is between 2 and 36
    // Assumes only valid characters are part of string
    BigInt(string s, int nBase);
  
   // Accessors
    // Print this BigInt and a newline
    void println();

   // Mutators
    // Add another BigInt to this one
    void add(BigInt b);

  private:
    vector<int> digits;
    int base;
};
#endif
