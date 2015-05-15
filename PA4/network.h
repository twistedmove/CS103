#ifndef NETWORK_H
#define NETWORK_H

#include "user.h"
#include <string>
#include <vector>

using namespace std;

class Network {
 public:
 // Constructor(blank)
  Network();
  
 // Destructor(blank)
  ~Network();

 // Mutators
  // Returns 0 if successful or -1 if either user does
  //  not exist or connection already exists
  int add_connection(int uId, int uId2);
  // Returns 0 if successful or -1 and warning if new user's id 
  //  is not the end of the vector
  int add_user(User nUser);
  // Fills a network with users from a file of the proper
  //  format. This can only be done once per network and
  //  only before other users are added to the network.
  //  Returns 0 if successful or -1 if not.
  int read_friends(char* fName);
  // Returns 0 if successful or -1 if either user does 
  //  not exist or connection does not exist
  int remove_connection(int uId, int uId2);
  // Writes a network to a file in the proper format.
  //  Returns 0 if successful or -1 if not.
  int write_friends(char* fName);



 // Accessors
  // Returns name's id or -1 and warning if a user with the given
  //  name could not be found
  int get_id(string name);
  vector<User>* get_users();
  int get_users_size();
  // Prints id# name year zip, on one line and left-justified with
  //  a width of 20 for name and 6 for everything else 
  void print_user(int uId);

 private:
  vector<User> users;
};
#endif
