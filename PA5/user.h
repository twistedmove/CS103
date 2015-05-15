#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using namespace std;

class User {
 public:
 // Constructors
  // Friends and name default to empty, birthYr and zipCd default to 0
  User(int nId);
  // Friends defaults to empty
  User(int nId, int nBirthYr, int nZipCd, string nName);

 // Destructor(blank)
  ~User();

 // Mutators
  // Returns 0 if successful or -1 and warning if users are already friends.
  //  Only establishes connection one way.
  int add_friend(int fId);
  // Returns 0 if successful or -1 and warning if users are not friends.
  //  Only deletes connection one way.
  int delete_friend(int fId);
  // Returns index of fId location in user's friends vector 
  //  or -1 if not successful
  int find_friend_index(int fId);
  // Returns 0 if successful or -1 and warning and sets birth year to 0
  //  if year is not between 1000 and 9999
  int set_birth_yr(int nBirthYr);
  void set_name(string nName);
  // Returns 0 if successful or -1 if zip code is not between 10000 and 99999
  int set_zip_cd(int nZipCd);


 // Accessors
  int get_birth_yr();
  int get_id();
  string get_name();
  int get_zip_cd();
  vector<int>* get_friends();  

 // Public data members for the BFS
  int predecessor;

 private:
  int birthYr, id, zipCd;
  string name;
  vector<int> friends;
};
#endif
