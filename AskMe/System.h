#ifndef _SYSTEM_
#define _SYSTEM_

#include "QuestionManager.h"
#include "UserManager.h"

class System {
private:
  UserManager userMngr;
  QuestionManager questionMngr;
  static System *InestantSystem;

  System() = default;

  // Helper UI methods
  bool LogIn();
  bool SignUp();
  void PrintMenu() const;
  void Programe();
  bool EnterSystem();

  ~System();

public:
  static System *getIstantSystem();
  void start();
  void ClearMemory();
};

#endif