#include "bigint.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

BigInt::BigInt(string s)
{
  base = 10;

  for(int i = s.length()-1; i >= 0; i--)
    digits.push_back((int)s[i]-48);
}

BigInt::BigInt(string s, int nBase)
{
  base = nBase;

  for(int i = s.length()-1; i >= 0; i--)
  {
    if((int)s[i] >= 48 && (int)s[i] <= 57)
      digits.push_back((int)s[i]-48);
    else
      digits.push_back((int)s[i]-55);
  }
}

void BigInt::println()
{
  for(int i = digits.size()-1; i >= 0; i--)
  {
    if(digits[i] <= 9)
      cout << (char)(digits[i]+48);
    else
      cout << (char)(digits[i]+55);
  }
  cout << endl;
}

void BigInt::add(BigInt b)
{
  if(base != b.base)
  {
    cerr << "Cannot add BigInts with different bases." << endl;
    return;
  }

  // Fills the shorter BigInt with enough 0s to make them equal 
  if(digits.size() < b.digits.size())
  {
    while(digits.size() < b.digits.size())
      digits.push_back(0);
  }
  else if(digits.size() > b.digits.size())
  {
    while(b.digits.size() < digits.size())
      b.digits.push_back(0);
  }

  int remainder = 0;
  for(int i = 0; i < digits.size(); i++)
  {
    remainder = remainder + digits[i] + b.digits[i];
    digits[i] = remainder % base;
    remainder = remainder / base;
  }
  // Expands the BigInt when there is a remainder on the last spot
  if(remainder > 0)
    digits.push_back(remainder);
}
