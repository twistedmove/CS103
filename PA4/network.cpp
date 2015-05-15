#include "network.h"
#include "user.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
// Constructor
Network::Network()
{
}



// Destructor
Network::~Network()
{
}



// Mutators
int Network::add_connection(int uId, int uId2)
{
  // If the friend connection establishes one way
  if(users[uId].add_friend(uId2) == 0)
  {
    // Establish it the other way
    users[uId2].add_friend(uId);
    return 0;
  }
  else
    return -1;
}

int Network::add_user(User nUser)
{
  if(nUser.get_id() != (int)users.size())
  {
    cerr << "User id " << nUser.get_id() << " does not equal expected id "
            << users.size() << endl
         << "Cannot add non-sequential user." << endl;
    return -1;
  }
  else
  {
    users.push_back(nUser);
    return 0;
  }
}

int Network::read_friends(char* fName)
{
  // Try to open file
  ifstream inFile(fName);
  if(inFile.fail())
  {
    cerr << "Error opening file: " << fName << endl;
    return -1;
  }

  // Try to get number of users in network
  int numUsers;
  inFile >> numUsers;
  if(inFile.fail())
  {
    inFile.close();
    cerr << "Number of users not specified." << endl;
    return -1;
  }

  // Get the users' information for the number of them specified
  // Quits with an error anytime the expected info was not found.
  for(int i = 0; i < numUsers; i++)
  {
    // Temporary variables to shuttle in the user info
    int tempInt;
    string tempStr, tempStr2;
    istringstream fileLine;

    // Create and add a user with the input Id
    inFile >> tempInt;
    if(inFile.fail())
    {
      inFile.close();
      cerr << "Unable to find ID " << i << endl
           << i << " user(s) created." << endl;
      return -1;
    }
    if(add_user(User(tempInt)) == -1)
    {
      inFile.close();
      cerr << i << " user(s) created." << endl;
      return -1;
    }

    // Find and skip the tab to reach name line, get the user's name, store it
    inFile.ignore(10,'\t');
    inFile >> tempStr >> tempStr2;
    tempStr = tempStr + " " + tempStr2;
    users[i].set_name(tempStr);

    // Get and store the user's birth year
    inFile >> tempInt;
    if(inFile.fail())
    {
      inFile.close();
      cerr << "No number found after name for user " << i << endl
           << i+1 << " user(s) created." << endl;
      return -1;
    }
    users[i].set_birth_yr(tempInt);

    // Get and store the user's zip code
    inFile >> tempInt;
    if(inFile.fail())
    {
      inFile.close();
      cerr << "No number found after birth year for user " << i << endl
           << i+1 << " user(s) created." << endl;
      return -1;
    }
    users[i].set_zip_cd(tempInt);

    // Get and store the users' friends
     // Find and skip the tab to reach friend line
     inFile.ignore(10,'\t');
     getline(inFile, tempStr);
     fileLine.str(tempStr);
     // Read in friend ids from a string stream until it fails
     while(fileLine >> tempInt)
       users[i].add_friend(tempInt);
  }

  inFile.close();
  return 0; 
}

int Network::remove_connection(int uId, int uId2)
{
  // If the the friend connection deletes ones way
  if(users[uId].delete_friend(uId2) == 0)
  {
    // Delete it the other way
    users[uId2].delete_friend(uId);
    return 0;
  }
  else
    return -1;
}

int Network::write_friends(char* fName)
{
  ofstream outFile(fName);
  if(outFile.fail())
  {
    cerr << "Error opening file: " << fName << endl;
    return -1;
  }

  outFile << users.size() << endl;

  for(int i = 0; i < (int)users.size(); i++)
  {
    outFile << i << endl
            << '\t' << users[i].get_name() << endl
            << '\t' << users[i].get_birth_yr() << endl
            << '\t' << users[i].get_zip_cd() << endl
            << '\t';
    vector<int>* vecPtr = users[i].get_friends();
    for(unsigned int j = 0; j < vecPtr->size(); j++)
      outFile << (*vecPtr)[j] << " ";
    outFile << endl;
  }

  outFile.close();
  return 0;
}



// Accessors
int Network::get_id(string name)
{
  for(int i = 0; i < (int)users.size(); i++)
  {
    if(users[i].get_name() == name)
      return i;
  }

  cerr << "Unable to find user: " << name << endl;
  return -1;
}

vector<User>* Network::get_users()
{
  return &users;
}

int Network::get_users_size()
{
  return users.size();
}

void Network::print_user(int uId)
{ // Justifies everything left
  cout << left;
  cout << setw(6) << uId << setw(22) << users[uId].get_name() << setw(6)
          << users[uId].get_birth_yr() << setw(6) << users[uId].get_zip_cd()
          << endl;
}
