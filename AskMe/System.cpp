#include "System.h"

System *System::InestantSystem = nullptr;

System *System::getIstantSystem() {
  if (InestantSystem == nullptr)
    InestantSystem = new System();
  return InestantSystem;
}

void System::start() {
  while (true) {
    if (EnterSystem())
      Programe();
    else {
      std::cout << "EXITING PROGRAM...\n";
      return;
    }
  }
}

bool System::EnterSystem() {
  while (true) {
    std::cout << "\n==============================\n";
    std::cout << "   WELCOME TO ASK ME SYSTEM   \n";
    std::cout << "==============================\n";
    std::cout << "  [1] Log In\n";
    std::cout << "  [2] Sign Up\n";
    std::cout << "  [3] Exit\n";
    std::cout << "------------------------------\n";
    std::cout << "Choice: ";

    int choice;
    if (!(std::cin >> choice)) {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      continue;
    }

    if (choice == 1) {
      if (LogIn())
        return true;
    } else if (choice == 2) {
      if (SignUp())
        return true;
    } else if (choice == 3)
      return false;
    else
      std::cout << "Invalid choice!\n";
  }
}

bool System::LogIn() {
  std::string user, pass;
  std::cout << "Username: ";
  std::cin >> user;
  std::cout << "Password: ";
  std::cin >> pass;

  if (userMngr.loadUser(user, pass)) {
    std::cout << "\nWelcome back, " << user << "!\n";
    return true;
  }
  std::cout << "Invalid username or password.\n";
  return false;
}

bool System::SignUp() {
  std::string user, pass;
  std::cout << "Enter new username: ";
  std::cin >> user;
  std::cout << "Create a password: ";
  std::cin >> pass;

  if (userMngr.signUp(user, pass)) {
    std::cout << "Account created! Welcome, " << user << ".\n";
    return true;
  }
  std::cout << "Username already exists!\n";
  return false;
}

void System::Programe() {
  while (true) {
    PrintMenu();
    int choice;
    std::cout << "Choice: ";
    if (!(std::cin >> choice)) {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      continue;
    }

    int curUserId = userMngr.getActiveUser().getId();

    if (choice == 1)
      questionMngr.printQuestions(curUserId, 1);
    else if (choice == 2)
      questionMngr.printQuestions(curUserId, 2);
    else if (choice == 3)
      questionMngr.answerQuestion(curUserId);
    else if (choice == 4)
      questionMngr.deleteQuestion(curUserId);
    else if (choice == 5)
      questionMngr.askQuestion(curUserId);
    else if (choice == 6)
      userMngr.listUsers();
    else if (choice == 7)
      questionMngr.printQuestions(curUserId, 7);
    else if (choice == 8) {
      userMngr.logout();
      return;
    } else if (choice == 9) {
      ClearMemory();
      std::exit(0);
    } else
      std::cout << "Invalid choice!\n";
  }
}

void System::PrintMenu() const {
  std::cout << "\n============================================\n";
  std::cout << "               MAIN MENU                    \n";
  std::cout << "============================================\n";
  std::cout << "  [1] Print Questions To Me\n";
  std::cout << "  [2] Print Questions From Me\n";
  std::cout << "  [3] Answer Question\n";
  std::cout << "  [4] Delete Question\n";
  std::cout << "  [5] Ask Question\n";
  std::cout << "  [6] List System Users\n";
  std::cout << "  [7] Feed\n";
  std::cout << "--------------------------------------------\n";
  std::cout << "  [8] Logout\n";
  std::cout << "  [9] EXIT\n";
  std::cout << "============================================\n";
}

void System::ClearMemory() {
  if (InestantSystem != nullptr)
    delete InestantSystem;
  InestantSystem = nullptr;
}

System::~System() {}
