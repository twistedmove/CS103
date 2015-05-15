#include "user.h"
#include <iostream>

using namespace std;
// Constructors
User::User(int nId)
{
  id = nId;
  birthYr = 0;
  zipCd = 0;
}

User::User(int nId, int nBirthYr, int nZipCd, string nName)
{
  id = nId;
  set_birth_yr(nBirthYr);
  set_zip_cd(nZipCd);
  set_name(nName);
}



// Destructor
User::~User()
{
}



// Mutators
int User::add_friend(int fId)
{
  int idIndex = find_friend_index(fId);

  if(idIndex != -1)
  {
    cerr << "User " << id << " and user " << fId
            << " are already friends" << endl;
    return -1;
  }
  else
  {
    friends.push_back(fId);
    return 0;
  }
}

int User::delete_friend(int fId)
{
  int idIndex = find_friend_index(fId);

  if(idIndex == -1)
  {
    cerr << "User " << id << " and user " << fId 
            << " are not friends." << endl;
    return -1;
  }
  else
  {
    friends.erase(friends.begin() + idIndex);
    return 0;
  }
}

int User::find_friend_index(int fId)
{
  for(int i = 0; i < (int)friends.size(); i++)
  {
    if(friends[i] == fId)
      return i;
  }

  return -1;
}

int User::set_birth_yr(int nBirthYr)
{
  if(nBirthYr > 999 && nBirthYr < 10000)
  {
    birthYr = nBirthYr;
    return 0;
  }
  else
  {
    birthYr = 0;
    cerr << "Invalid birth year for user " << id << endl
         << "Accepted range: 1000-9999 inclusive" << endl
         << "Defaulting to 0" << endl;
    return -1;
  }
}

void User::set_name(string nName)
{
  name = nName;
}

int User::set_zip_cd(int nZipCd)
{
  if(nZipCd > 9999 && nZipCd < 100000)
  {
    zipCd = nZipCd;
    return 0;
  }
  else
  {
    zipCd = 0;
    cerr << "Invalid zip code for user " << id << endl
         << "Accepted : 10000 to 99999 inclusive" << endl
         << "Defaulting to 0" << endl;
    return -1;
  }
}



// Accessors
int User::get_birth_yr()
{
  return birthYr;
}

int User::get_id()
{
  return id;
}

string User::get_name()
{
  return name;
}

int User::get_zip_cd()
{
  return zipCd;
}

vector<int>* User::get_friends()
{
  return &friends;
}
