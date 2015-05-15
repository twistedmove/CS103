#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2)
   {
    cout << argv[0] << " expects a string to be entered"
         << " on the command line"  << endl;
    return 1;
   }
  cout << "Hello " << argv[1] << ". Welcome to CS101." << endl;
  return 0;
}
