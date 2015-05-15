#include "network.h"
#include "user.h"
#include <deque>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

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

string Network::get_name(int uId)
{
  if(uId > (int)users.size()-1)
  {
    cerr << "Invalid user " << uId << endl;
    return "";
  }
  else
    return users[uId].get_name();
}

vector<User>* Network::get_users()
{
  return &users;
}

int Network::get_users_size()
{
  return users.size();
}



// Utilities
vector<vector<int> > Network::groups()
{
  vector<vector<int> > groups;

  // Set up a dynamic array of all possible users to remember if
  //  they've been checked and initialize to false
  bool* visited = new bool[users.size()];
  for(int i = 0; i < (int)users.size(); i++)
    visited[i] = false;

  // Found is used to quit BFS without checking every user if possible
  bool found = false;

  for(int i = 0; i < (int)users.size(); i++)
  {
    // If one of the users hasn't been examined, it is part of a set
    if(!visited[i])
    {
      visited[i] = true;
      
      // Create a disjoint set to remember all the users branching off
      //  from the initial one using BFS with a non-existant target
      vector<int> disjointSet = target_srch(visited, i, -1, found);
      groups.push_back(disjointSet);
    }
  }

  // Delete the visited array that is no longer needed
  delete [] visited;

  return groups;
}

void Network::print_user(int uId)
{ // Justifies everything left
  cout << left;
  cout << setw(6) << uId << setw(22) << users[uId].get_name() << setw(6)
          << users[uId].get_birth_yr() << setw(6) << users[uId].get_zip_cd()
          << endl;
}

vector<int> Network::shortest_path(int from, int to)
{
  // Set up a dynamic array of all possible users to remember if
  //  they've been checked and initialize to false
  bool* visited = new bool[users.size()];
  for(int i = 0; i < (int)users.size(); i++)
    visited[i] = false;

  // Found is used to quit BFS without checking every user if possible
  bool found = false;

  target_srch(visited, from, to, found);

  // Delete the visited array that is no longer needed
  delete [] visited;

  vector<int> shortPath;
  if(!found)
    return shortPath;
  else
  {
    vector<int> revShortPath;
    revShortPath.push_back(to);
    // Adds valid predecessors to the reverse vector
    while(users[revShortPath.back()].predecessor != -1)
      revShortPath.push_back(users[revShortPath.back()].predecessor);

    // Reverses through the reverse vector to provide the path
    for(int i = revShortPath.size()-1; i >= 0; i--)
      shortPath.push_back(revShortPath[i]);
    return shortPath;
  }
}

vector<int> Network::suggest_friends(int who, int& score)
{
  // Set up a dynamic array of all possible users to avoid suggesting
  //  the user or a current friend. Initialize to false
  bool* alreadyFriend = new bool[users.size()];
  for(int i = 0; i < (int)users.size(); i++)
    alreadyFriend[i] = false;

  alreadyFriend[who] = true;
  // Mark all friends as already friends
  vector<int>* layer1 = users[who].get_friends();
  for(int i = 0; i < (int)layer1->size(); i++)
    alreadyFriend[(*layer1)[i]] = true;

  // Store suggestable users and the number of times they appear in a vector
  vector<vector<int> > suggestedWScore;
  int maxScore = -1;

  // Go through all users 2 layers below given user "who"
  for(int i = 0; i < (int)layer1->size(); i++)
  {
    vector<int>* layer2 = users[(*layer1)[i]].get_friends();
    for(int j = 0; j < (int)layer2->size(); j++)
    {
      // If the user is not already a friend
      if(!alreadyFriend[(*layer2)[j]])
      {
        bool stored = false;

        for(int k = 0; k < (int)suggestedWScore.size(); k++)
        {
          // If the user has been pinged already, update their score by one
          if(suggestedWScore[k][0] == (*layer2)[j])
          {
            suggestedWScore[k][1]++;
            stored = true;
            // Update the max score if a bigger one is created
            if(maxScore < suggestedWScore[k][1])
              maxScore = suggestedWScore[k][1];
            // Stop looking for the user as soon as you know they've been pinged
            k = suggestedWScore.size();
          }
        }
        // If the user has not been pinged already, add to the vector
        if(stored == false)
        {
          vector<int> temp;
          temp.push_back((*layer2)[j]);
          temp.push_back(1);
          suggestedWScore.push_back(temp);
          // For the first suggestable user update max score
          if(maxScore == -1)
            maxScore = 1;
        }
      }
    }
  }

  // Delete the already friend array that is no longer needed
  delete [] alreadyFriend;

  vector<int> suggest;
  score = maxScore;
  if(maxScore == -1)
    return suggest;
  else
  {
    for(int i = 0; i < (int)suggestedWScore.size(); i++)
    {
      if(suggestedWScore[i][1] == maxScore)
        suggest.push_back(suggestedWScore[i][0]);
    }
    return suggest;
  }
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



// Helper
vector<int> Network::target_srch(bool* visit, int start, int end, bool &found)
{
  deque<int> queue;
  vector<int> path;

  // The source user's predecessor is -1 and it is added to the queue
  users[start].predecessor = -1;
  path.push_back(start);
  visit[start] = true;
  queue.push_back(start);

  while(queue.size() != 0 && found == false)
  {
    // Search through the friend list of the user at the front of the queue
    vector<int>* friendList = users[queue.front()].get_friends();
    for(int i = 0; i < (int)friendList->size(); i++)
    {
      // Ensure users aren't added to the queue multiple times
      if(!visit[(*friendList)[i]])
      {
        visit[(*friendList)[i]] = true;

        users[(*friendList)[i]].predecessor = queue.front();
        path.push_back((*friendList)[i]);

        queue.push_back((*friendList)[i]);
        if((*friendList)[i] == end)
          found = true;
      }
    }
    // Delete the user at the front of the queue after searching all friends
    queue.pop_front();
  }

  return path;
}
