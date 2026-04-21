#ifndef QUESTION_MANAGER_H
#define QUESTION_MANAGER_H

#include "Question.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class QuestionManager {
private:
  std::string questionsFile = "questions.csv";

  // Helper to find all questions relevant to a user or all
  std::map<int, std::pair<Question, std::vector<Question>>>
  loadQuestions(int userId, int dir) const;

public:
  QuestionManager() = default;

  void askQuestion(int senderId);
  void answerQuestion(int receiverId);
  void deleteQuestion(int userId);
  void printQuestions(int userId, int dir) const;

  int getNextId() const;
};

#endif
