#include "network.h"
#include "user.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void dispMenu();

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
  while(select >= 1 && select <= 6)
  {
    dispMenu();
    cin >> select;

    // Option 1, add user
    if(select == 1)
    {
      int num1, num2;
      string name1, name2;

      cin >> name1 >> name2 >> num1 >> num2;
      name1 = name1+" "+name2;
      socialNet.add_user(User(socialNet.get_users_size(),num1,num2,name1));
    }
    // Option 2, add friend connection
    else if(select == 2)
    {
      string name1, name2, name3;
      
      // Get first user's id
      cin >> name1 >> name2;
      name1 = name1+" "+name2;
      int uId = socialNet.get_id(name1);
      // Get second user's id
      cin >> name2 >> name3;
      name2 = name2+" "+name3;
      int uId2 = socialNet.get_id(name2);
      socialNet.add_connection(uId, uId2);
    }
    // Option 3, remove friend connection
    else if(select == 3)
    {
      string name1, name2, name3;
      
      // Get first user's id
      cin >> name1 >> name2;
      name1 = name1+" "+name2;
      int uId = socialNet.get_id(name1);
      // Get second user's id
      cin >> name2 >> name3;
      name2 = name2+" "+name3;
      int uId2 = socialNet.get_id(name2);
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
      string name1, name2;

      cin >> name1 >> name2;
      name1 = name1+" "+name2;
      int uId = socialNet.get_id(name1);
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
       << "   (Provide file name on same line)"                       << endl;
}
