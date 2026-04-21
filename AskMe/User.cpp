#include "User.h"

void User::setUserName(std::string _userName) {
    userName = _userName;
}

void User::setId(int _id) {
    id = _id;
}

std::string User::getUserName() const{
    return userName;
}

int User::getId() const{
    return id;
}