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

 // Accessors
  // Returns name's id or -1 and warning if a user with the given
  //  name could not be found
  int get_id(string name);
  // Returns uId's name or a blank string and warning if the
  //  given id is invalid
  string get_name(int uId);
  vector<User>* get_users();
  int get_users_size();

 // Utilities
  // Computes how many disjoint sets are in the network and returns
  //  a vector of each of these components by user id
  vector<vector<int> > groups();
  // Prints id# name year zip, on one line and left-justified with
  //  a width of 20 for name and 6 for everything else 
  void print_user(int uId);
  // A shortest path starting at user "from" and ending at
  //  user "to." Returns empty vector if no path exists
  vector<int> shortest_path(int from, int to);
  // Suggested friends at a depth of two with highest score(appearances)
  //  for user who. Fills in score at given pointer. If no suggestions
  //  exist, returns empty vector and score is set to -1
  vector<int> suggest_friends(int who, int& score);
  // Writes a network to a file in the proper format.
  //  Returns 0 if successful or -1 if not
  int write_friends(char* fName);

 private:
  vector<User> users;

 // Helper
  // Executes a breadth first search starting at from and ending at to.
  //  Updates found if successful and returns a vector of all nodes visited.
  //  Sets the predecessors of all nodes visited
  vector<int> target_srch(bool* visited, int from, int to, bool &found);
};
#endif
