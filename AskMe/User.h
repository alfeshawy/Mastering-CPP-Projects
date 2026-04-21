#ifndef _USER_
#define _USER_

#include <string>

class User {
private:
  std::string userName;
  int id;

public:
  User() : id(-1) {}
  User(int _id, std::string _userName) : id(_id), userName(_userName) {}
  void setUserName(std::string _userName);
  void setId(int _id);
  std::string getUserName() const;
  int getId() const;
};

#endif