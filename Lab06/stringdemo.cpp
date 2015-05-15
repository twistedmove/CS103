#include <iostream>
#include <cstring>

using namespace std;

int main()
{
  char mystring[80] = "ComputerScience";
  char yourstring[80];
  char* astring;

//  yourstring = mystring;
//  strncpy(astring, mystring, 80);

  astring = mystring;
  strncpy(yourstring, mystring, 80);
  cout << astring << endl;
  cout << yourstring << endl;

  mystring[0] = '*';
  cout << astring << endl;
  cout << yourstring << endl;

  return 0;
}
