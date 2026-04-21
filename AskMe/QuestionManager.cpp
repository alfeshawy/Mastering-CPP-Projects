#include "QuestionManager.h"
#include <algorithm>

int QuestionManager::getNextId() const {
  std::fstream file(questionsFile, std::ios::in);
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

std::map<int, std::pair<Question, std::vector<Question>>>
QuestionManager::loadQuestions(int userId, int dir) const {
  std::map<int, std::pair<Question, std::vector<Question>>> questions;
  std::fstream file(questionsFile, std::ios::in);
  std::string line;

  while (getline(file, line)) {
    if (line.empty())
      continue;
    std::stringstream ss(line);
    std::string s_id, s_parent, s_send, s_recv, s_q, s_a;

    getline(ss, s_id, '|');
    getline(ss, s_parent, '|');
    getline(ss, s_send, '|');
    getline(ss, s_recv, '|');
    getline(ss, s_q, '|');
    getline(ss, s_a, '|');

    int rId = std::stoi(s_recv);
    int sId = std::stoi(s_send);

    bool match = false;
    if (dir == 7)
      match = true; // Feed
    else if (dir == 1 && rId == userId)
      match = true; // To me
    else if (dir == 2 && sId == userId)
      match = true; // From me

    if (match) {
      Question q;
      q.setId(std::stoi(s_id));
      q.setParent(std::stoi(s_parent));
      q.setSender(sId);
      q.setReceiver(rId);
      q.setQuestion(s_q);
      q.setAnswer(s_a);

      if (q.getParent() == -1)
        questions[q.getId()].first = q;
      else
        questions[q.getParent()].second.push_back(q);
    }
  }
  file.close();
  return questions;
}

void QuestionManager::printQuestions(int userId, int dir) const {
  auto questions = loadQuestions(userId, dir);
  for (auto const &[id, group] : questions) {
    if (group.first.getId() == 0)
      continue; // Skip if parent not loaded (e.g. dir=1/2 filters)

    std::cout << "\n--------------------------------------------------\n";
    std::cout << "[Question ID: " << group.first.getId() << "]";
    if (dir != 1)
      std::cout << " To User: " << group.first.getReceiver();
    if (dir != 2)
      std::cout << " From User: " << group.first.getSender();
    std::cout << "\n    Question: " << group.first.getQuestion() << "\n";
    std::cout << "    Answer  : "
              << (group.first.getAnswer().empty() ? "NOT ANSWERED YET"
                                                  : group.first.getAnswer())
              << "\n";

    for (const auto &thread : group.second) {
      std::cout << "  ↳ [Thread ID: " << thread.getId() << "]";
      if (dir != 1)
        std::cout << " To User: " << thread.getReceiver();
      if (dir != 2)
        std::cout << " From User: " << thread.getSender();
      std::cout << "\n    Question: " << thread.getQuestion() << "\n";
      std::cout << "    Answer  : "
                << (thread.getAnswer().empty() ? "NOT ANSWERED YET"
                                               : thread.getAnswer())
                << "\n";
    }
  }
}

void QuestionManager::askQuestion(int senderId) {
  int targetId, parentId = -1;
  std::cout << "Enter User ID or -1 to cancel: ";
  std::cin >> targetId;
  if (targetId == -1)
    return;

  std::cout << "Is this a thread question? (1 for Yes, 0 for No): ";
  int isThread;
  std::cin >> isThread;
  if (isThread) {
    std::cout << "Enter Parent Question ID: ";
    std::cin >> parentId;
  }

  std::string text;
  std::cout << "Enter question text: ";
  std::cin.ignore();
  getline(std::cin, text);

  int id = getNextId();
  std::fstream file(questionsFile, std::ios::app);
  file << id << "|" << parentId << "|" << senderId << "|" << targetId << "|"
       << text << "|\n";
  file.close();
  std::cout << "Question sent! (ID: " << id << ")\n";
}

void QuestionManager::answerQuestion(int receiverId) {
  int qId;
  std::cout << "Enter Question ID to answer: ";
  std::cin >> qId;

  std::vector<std::string> lines;
  std::fstream file(questionsFile, std::ios::in);
  std::string line;
  bool found = false;

  while (getline(file, line)) {
    if (line.empty())
      continue;
    std::stringstream ss(line);
    std::string s_id, s_parent, s_send, s_recv, s_q, s_a;
    getline(ss, s_id, '|');
    getline(ss, s_parent, '|');
    getline(ss, s_send, '|');
    getline(ss, s_recv, '|');
    getline(ss, s_q, '|');
    getline(ss, s_a, '|');

    if (std::stoi(s_id) == qId) {
      if (std::stoi(s_recv) != receiverId) {
        std::cout << "Error: Not your question.\n";
        file.close();
        return;
      }
      std::cout << "Question: " << s_q << "\n";
      std::cout << "Answer  : ";
      std::cin.ignore();
      getline(std::cin, s_a);
      line = s_id + "|" + s_parent + "|" + s_send + "|" + s_recv + "|" + s_q +
             "|" + s_a + "|";
      found = true;
    }
    lines.push_back(line);
  }
  file.close();

  if (!found) {
    std::cout << "Error: ID not found.\n";
    return;
  }

  std::fstream outFile(questionsFile, std::ios::out);
  for (const auto &l : lines)
    outFile << l << "\n";
  outFile.close();
  std::cout << "Answered!\n";
}

void QuestionManager::deleteQuestion(int userId) {
  int qId;
  std::cout << "Enter Question ID to delete: ";
  std::cin >> qId;

  std::vector<std::string> allLines;
  std::fstream file(questionsFile, std::ios::in);
  std::string line;

  bool canDelete = false;
  // Pass 1: Permission check
  while (getline(file, line)) {
    std::stringstream ss(line);
    std::string s_id, s_parent, s_send, s_recv;
    getline(ss, s_id, '|');
    getline(ss, s_parent, '|');
    getline(ss, s_send, '|');
    getline(ss, s_recv, '|');
    if (std::stoi(s_id) == qId) {
      if (std::stoi(s_send) == userId || std::stoi(s_recv) == userId)
        canDelete = true;
      break;
    }
  }
  file.close();

  if (!canDelete) {
    std::cout << "Error: Not found or no permission.\n";
    return;
  }

  // Pass 2: Filter out the question and ALL its descendants (recursively by ID)
  std::vector<int> toDelete = {qId};
  file.open(questionsFile, std::ios::in);
  // This is a simple iterative approach for one-level threading as implemented.
  // To handle deeper threads, we'd need to loop until no more IDs are added.
  bool added;
  do {
    added = false;
    std::vector<std::string> tempLines;
    file.clear();
    file.seekg(0);
    while (getline(file, line)) {
      std::stringstream ss(line);
      std::string s_id, s_parent;
      getline(ss, s_id, '|');
      getline(ss, s_parent, '|');
      int curParent = std::stoi(s_parent);
      int curId = std::stoi(s_id);

      // If parent is in toDelete, but current ID is not, add it
      if (std::find(toDelete.begin(), toDelete.end(), curParent) !=
          toDelete.end()) {
        if (std::find(toDelete.begin(), toDelete.end(), curId) ==
            toDelete.end()) {
          toDelete.push_back(curId);
          added = true;
        }
      }
    }
  } while (added);
  file.close();

  // Final filter
  file.open(questionsFile, std::ios::in);
  while (getline(file, line)) {
    std::stringstream ss(line);
    std::string s_id;
    getline(ss, s_id, '|');
    if (std::find(toDelete.begin(), toDelete.end(), std::stoi(s_id)) ==
        toDelete.end()) {
      allLines.push_back(line);
    }
  }
  file.close();

  std::fstream outFile(questionsFile, std::ios::out);
  for (const auto &l : allLines)
    outFile << l << "\n";
  outFile.close();
  std::cout << "Deleted question and threads.\n";
}
