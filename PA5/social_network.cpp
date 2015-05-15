#include "network.h"
#include "user.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void dispMenu();
string getInputName();

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    cerr << "Usage: ./social_network user_database_file.txt" << endl;
    return 1;
  }

  // Initialize a network from the file
  Network socialNet;
  // Quit if the reading failed
  if(socialNet.read_friends(argv[1]) == -1)
    return 1;

  int select = 1;
  // Loops menu
  while(select >= 1 && select <= 9)
  {
    dispMenu();
    cin >> select;

    // Option 1, add user
    if(select == 1)
    {
      int num1, num2;
      string name = getInputName();

      cin >> num1 >> num2;
      socialNet.add_user(User(socialNet.get_users_size(),num1,num2,name));
    }
    // Option 2, add friend connection
    else if(select == 2)
    {
      string name1 = getInputName(), name2 = getInputName();
      
      // Get both user's ids
      int uId = socialNet.get_id(name1);
      int uId2 = socialNet.get_id(name2);
      if(uId != -1 && uId2 != -1)
        socialNet.add_connection(uId, uId2);
    }
    // Option 3, remove friend connection
    else if(select == 3)
    {
      string name1 = getInputName(), name2 = getInputName();
      
      // Get both user's ids
      int uId = socialNet.get_id(name1);
      int uId2 = socialNet.get_id(name2);
      if(uId != -1 && uId2 != -1)
        socialNet.remove_connection(uId, uId2);
    }
    // Option 4, print users
    else if(select == 4)
    {
      // Left-justifies everything
      cout << left;
      // Table header
      cout << setw(6) << "ID" << setw(22) << "Name" << setw(6) << "Year"
              << setw(6) << "Zip" << endl
      // Table divider of '='s
           << setfill('=') << setw(40) << "" << setfill(' ') << endl;
      // Table contents
      for(int i = 0; i < socialNet.get_users_size(); i++)
        socialNet.print_user(i);
    }
    // Option 5, list friends
    else if(select == 5)
    {
      string name = getInputName();

      int uId = socialNet.get_id(name);
      // If a user with the given name was found
      if(uId != -1)
      {
        // Acquire that user's friends list
        vector<User>* userList = socialNet.get_users();
        vector<int>* friendList = (*userList)[uId].get_friends();

        // Left-justifies everything
        cout << left;
        // Table header
        cout << setw(6) << "ID" << setw(22) << "Name" << setw(6) << "Year"
                << setw(6) << "Zip" << endl
        // Table divider of '='s
             << setfill('=') << setw(40) << "" << setfill(' ') << endl;
        // Table contents
        for(int i = 0; i < (int)(*friendList).size(); i++)
        {
          int fId = (*friendList)[i];
          socialNet.print_user(fId);
        }
      }
    }
    // Option 6, write to file
    else if(select == 6)
    {
      string fName;

      cin >> fName;
      socialNet.write_friends((char*)fName.c_str());
    }
    // Option 7, find shortest path
    else if(select == 7)
    {
      string name1 = getInputName(), name2 = getInputName();
      int uId = socialNet.get_id(name1), uId2 = socialNet.get_id(name2);

      if(uId != -1 && uId2 != -1)
      {
        vector<int> shortPath = socialNet.shortest_path(uId, uId2);
        if(shortPath.size() == 0)
          cout << "None" << endl;
        else
        {
          cout << "Distance: " << shortPath.size()-1 << endl;
          for(int i = 0; i < (int)shortPath.size()-1; i++)
            cout << socialNet.get_name(shortPath[i]) << " -> ";
          // Last link is output separately to avoid an extra space
          cout << socialNet.get_name(shortPath.back()) << endl;
        }
      } 
    }
    // Option 8, print all disjoint sets
    else if(select == 8)
    {
      vector<vector<int> > groups = socialNet.groups();
      // Loop through all disjoint sets
      for(int i = 0; i < (int)groups.size(); i++)
      {
        cout << "Set " << i+1 << " => ";
        // Loop through all members of a disjoint set
        for(int j = 0; j < (int)groups[i].size()-1; j++)
          cout << socialNet.get_name(groups[i][j]) << ", ";
        // Last user in set is output separately to avoid extra comma and space
        cout << socialNet.get_name(groups[i][groups[i].size()-1]) << endl;
      }
    }
    // Option 9, suggest friends
    else if(select == 9)
    {
      string name = getInputName();
      int uId = socialNet.get_id(name);
      if(uId != -1)
      {
        int score;
        vector<int> suggested = socialNet.suggest_friends(uId, score);
        if(score == -1)
          cout << "None" << endl;
        else
        {
          cout << "The suggested friend(s) is/are: " << endl;
          for(int i = 0; i < (int)suggested.size(); i++)
          {
           cout << "  " << left << setw(22) << socialNet.get_name(suggested[i])
                << "Score: " << score << endl;
          }
        }
      }
    }
  }

  return 0;
}



void dispMenu()
{
  cout << "***************Social Network Manager Menu***************" << endl
       << "Enter an option number and press return"                   << endl
       << "1: Add a user"                                             << endl
       << "   (Provide full name, birth year, zip code on same line)" << endl
       << "2: Add friend connection"                                  << endl
       << "   (Provide both full names on same line)"                 << endl
       << "3: Remove friend connection"                               << endl
       << "   (Provide both full names on same line)"                 << endl
       << "4: Print all users"                                        << endl
       << "5: Print friends"                                          << endl
       << "   (Provide full name on same line)"                       << endl
       << "6: Write to file"                                          << endl
       << "   (Provide file name on same line)"                       << endl
       << "7: Find shortest path between two users"                   << endl
       << "   (Provide both full names on same line)"                 << endl
       << "8: Print out all linked groups of users"                   << endl
       << "9: Suggest friends for a user"                             << endl
       << "   (Provide full name on same line)"                       << endl;
}

string getInputName()
{
  string firstName, lastName;

  cin >> firstName >> lastName;
  return firstName+" "+lastName;
}
