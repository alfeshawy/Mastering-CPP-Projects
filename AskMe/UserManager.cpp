#include "UserManager.h"

bool UserManager::loadUser(const std::string &username,
                           const std::string &password) {
  std::fstream file(usersFile, std::ios::in);
  if (!file.is_open())
    return false;

  std::string line;
  while (getline(file, line)) {
    std::stringstream ss(line);
    std::string s_id, s_user, s_pass;
    getline(ss, s_id, '|');
    getline(ss, s_user, '|');
    getline(ss, s_pass, '|');

    if (s_user == username && s_pass == password) {
      activeUser.setId(std::stoi(s_id));
      activeUser.setUserName(s_user);
      file.close();
      return true;
    }
  }
  file.close();
  return false;
}

bool UserManager::userExists(const std::string &username) const {
  std::fstream file(usersFile, std::ios::in);
  if (!file.is_open())
    return false;

  std::string line;
  while (getline(file, line)) {
    std::stringstream ss(line);
    std::string s_id, s_user;
    getline(ss, s_id, '|');
    getline(ss, s_user, '|');
    if (s_user == username) {
      file.close();
      return true;
    }
  }
  file.close();
  return false;
}

int UserManager::getNextId() const {
  std::fstream file(usersFile, std::ios::in);
  int maxId = 0;
  std::string line;
  while (getline(file, line)) {
    std::stringstream ss(line);
    std::string s_id;
    getline(ss, s_id, '|');
    if (!s_id.empty())
      maxId = std::max(maxId, std::stoi(s_id));
  }
  file.close();
  return maxId + 1;
}

bool UserManager::signUp(const std::string &username,
                         const std::string &password) {
  if (userExists(username))
    return false;

  int id = getNextId();
  std::fstream file(usersFile, std::ios::app);
  file << id << "|" << username << "|" << password << "\n";
  file.close();

  activeUser.setId(id);
  activeUser.setUserName(username);
  return true;
}

void UserManager::listUsers() const {
  std::fstream file(usersFile, std::ios::in);
  std::cout << "\n--- System Users ---\n";
  std::string line;
  while (getline(file, line)) {
    std::stringstream ss(line);
    std::string s_id, s_user, s_pass;
    getline(ss, s_id, '|');
    getline(ss, s_user, '|');
    std::cout << "ID: " << s_id << "\t Name: " << s_user << "\n";
  }
  std::cout << "--------------------\n";
  file.close();
}
