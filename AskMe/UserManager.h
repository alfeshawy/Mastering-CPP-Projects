#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "User.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class UserManager {
private:
  User activeUser;
  std::string usersFile = "users.csv";

public:
  UserManager() = default;

  bool loadUser(const std::string &username, const std::string &password);
  bool signUp(const std::string &username, const std::string &password);
  void listUsers() const;

  User getActiveUser() const { return activeUser; }
  bool isLoggedIn() const { return activeUser.getId() != -1; }
  void logout() {
    activeUser = User();
    activeUser.setId(-1);
  }

  bool userExists(const std::string &username) const;
  int getNextId() const;
};

#endif
