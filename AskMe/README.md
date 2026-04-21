<<<<<<< HEAD

=======
# AskMe - Professional CLI Q&A System

AskMe is a robust, command-line interface (CLI) application developed in C++ that simulates a social question-and-answer platform. It allows users to create accounts, ask questions to others, manage their incoming questions, and participate in threaded discussions.

## 🚀 Features

- **User Authentication**: Secure signup and login system.
- **Question Management**:
  - Ask anonymous or identified questions.
  - Answer questions received from other users.
  - Delete questions (including recursive thread deletion).
- **Threaded Discussions**: Support for sub-questions (threads) to allow for detailed conversations.
- **Global Feed**: View all public questions and answers in the system.
- **User Directory**: List all registered users to find people to ask.
- **Persistent Storage**: All data is saved in structured CSV files using a pipe (`|`) delimiter for maximum compatibility with text containing commas.

## 🏗️ Architecture

The project follows a modular, object-oriented design to ensure maintainability and scalability:

- **`System`**: The main controller that manages the application flow and user interface.
- **`UserManager`**: Handles user-related logic, including authentication, registration, and listing.
- **`QuestionManager`**: Manages the lifecycle of questions, including storage, retrieval, and deletion logic.
- **`User` & `Question`**: Core data models representing the entities in the system.

## 🛠️ Getting Started

### Prerequisites

- A C++ compiler (e.g., `g++`)
- Terminal or Command Prompt

### Compilation

Navigate to the project directory and run the following command:

```bash
g++ main.cpp System.cpp QuestionManager.cpp UserManager.cpp Question.cpp User.cpp -o AskMe
```

### Running the Application

Execute the compiled binary:

```bash
./AskMe
```

## 📂 Project Structure

```text
├── main.cpp              # Entry point
├── System.h/cpp          # Application controller & UI
├── UserManager.h/cpp     # User logic & Persistence
├── QuestionManager.h/cpp # Question logic & Persistence
├── User.h/cpp            # User data model
├── Question.h/cpp        # Question data model
├── users.csv             # User database (pipe-separated)
└── questions.csv         # Question database (pipe-separated)
```

## 💡 Technical Highlights

- **Comma Safety**: By using the `|` delimiter instead of a standard comma, the system can safely handle questions containing punctuation without corrupting the database.
- **Recursive Deletion**: Deleting a parent question automatically cleans up all associated replies, maintaining data integrity.
- **Singleton Pattern**: The `System` class uses a singleton-like approach to ensure a single instance manages the application state.

## 👤 Author

Developed as part of a C++ OOP & Data Structures learning project.
>>>>>>> 2bc4552 (Refactor: structure system into managers and implement Singleton pattern)
