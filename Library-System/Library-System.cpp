#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>

/**
 * @class Book
 * @brief Represents a book in the library.
 */
class Book {
private:
    int id;
    std::string name;
    int quantity;
    int borrowedCount;

public:
    Book(int id, std::string name, int quantity)
        : id(id), name(name), quantity(quantity), borrowedCount(0) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    int getBorrowedCount() const { return borrowedCount; }

    bool canBorrow() const { return borrowedCount < quantity; }
    
    void borrow() {
        if (canBorrow()) borrowedCount++;
    }

    void returnBook() {
        if (borrowedCount > 0) borrowedCount--;
    }

    // Sort helper
    static bool compareById(const Book& a, const Book& b) {
        return a.id < b.id;
    }

    static bool compareByName(const Book& a, const Book& b) {
        return a.name < b.name;
    }
};

/**
 * @class User
 * @brief Represents a library member who can borrow books.
 */
class User {
private:
    int id;
    std::string name;
    std::vector<std::string> borrowedBooks;

public:
    User(int id, std::string name) : id(id), name(name) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    const std::vector<std::string>& getBorrowedBooks() const { return borrowedBooks; }

    bool hasBorrowed(const std::string& bookName) const {
        return std::find(borrowedBooks.begin(), borrowedBooks.end(), bookName) != borrowedBooks.end();
    }

    void borrowBook(const std::string& bookName) {
        borrowedBooks.push_back(bookName);
    }

    void returnBook(const std::string& bookName) {
        auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), bookName);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
        }
    }
};

/**
 * @class LibraryManager
 * @brief Orchestrates all library operations and data management.
 */
class LibraryManager {
private:
    std::vector<Book> books;
    std::vector<User> users;

    // Helper for input validation
    int getValidInt(const std::string& prompt, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max()) {
        int val;
        while (true) {
            std::cout << prompt;
            if (std::cin >> val && val >= min && val <= max) {
                return val;
            }
            std::cout << "Invalid input! Please enter a valid number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // Finders
    Book* findBookByName(const std::string& name) {
        for (auto& b : books) {
            if (b.getName() == name) return &b;
        }
        return nullptr;
    }

    User* findUserByName(const std::string& name) {
        for (auto& u : users) {
            if (u.getName() == name) return &u;
        }
        return nullptr;
    }

public:
    void showMenu() {
        std::cout << "\n==========================================\n";
        std::cout << "          LIBRARY MANAGEMENT SYSTEM       \n";
        std::cout << "==========================================\n";
        std::cout << " 1) Add Book\n";
        std::cout << " 2) Search Books by Prefix\n";
        std::cout << " 3) Who Borrowed Book by Name\n";
        std::cout << " 4) Print Library by ID\n";
        std::cout << " 5) Print Library by Name\n";
        std::cout << " 6) Add User\n";
        std::cout << " 7) User Borrow a Book\n";
        std::cout << " 8) User Return a Book\n";
        std::cout << " 9) Print Users\n";
        std::cout << " 10) Exit\n";
        std::cout << "------------------------------------------\n";
    }

    void addBook() {
        std::string name;
        std::cout << "Enter book name: ";
        std::cin >> name;
        int id = getValidInt("Enter book ID: ");
        int quantity = getValidInt("Enter quantity: ", 1);

        books.emplace_back(id, name, quantity);
        std::cout << "Book added successfully.\n";
    }

    void searchBooksByPrefix() {
        std::string prefix;
        std::cout << "Enter search prefix: ";
        std::cin >> prefix;

        bool found = false;
        for (const auto& b : books) {
            if (b.getName().rfind(prefix, 0) == 0) {
                std::cout << " - " << b.getName() << " (ID: " << b.getId() << ")\n";
                found = true;
            }
        }
        if (!found) std::cout << "No books found matching this prefix.\n";
    }

    void printWhoBorrowedBook() {
        std::string bookName;
        std::cout << "Enter book name: ";
        std::cin >> bookName;

        Book* b = findBookByName(bookName);
        if (!b) {
            std::cout << "Invalid book name.\n";
            return;
        }

        bool foundAny = false;
        std::cout << "Users who borrowed '" << bookName << "':\n";
        for (const auto& u : users) {
            if (u.hasBorrowed(bookName)) {
                std::cout << " - " << u.getName() << "\n";
                foundAny = true;
            }
        }
        if (!foundAny) std::cout << "No users have borrowed this book.\n";
    }

    void printLibrarySorted(bool byId) {
        if (books.empty()) {
            std::cout << "Library is empty.\n";
            return;
        }

        std::vector<Book> tempBooks = books;
        if (byId) {
            std::sort(tempBooks.begin(), tempBooks.end(), Book::compareById);
        } else {
            std::sort(tempBooks.begin(), tempBooks.end(), Book::compareByName);
        }

        std::cout << "\n" << std::left << std::setw(10) << "ID" << std::setw(20) << "Name" 
                  << std::setw(10) << "Total" << std::setw(10) << "Borrowed" << "\n";
        std::cout << std::string(50, '-') << "\n";
        for (const auto& b : tempBooks) {
            std::cout << std::left << std::setw(10) << b.getId() << std::setw(20) << b.getName() 
                      << std::setw(10) << b.getQuantity() << std::setw(10) << b.getBorrowedCount() << "\n";
        }
    }

    void addUser() {
        std::string name;
        std::cout << "Enter user name: ";
        std::cin >> name;
        int id = getValidInt("Enter user ID: ");

        users.emplace_back(id, name);
        std::cout << "User added successfully.\n";
    }

    void borrowBook() {
        std::string userName, bookName;
        std::cout << "Enter user name: ";
        std::cin >> userName;
        std::cout << "Enter book name: ";
        std::cin >> bookName;

        User* u = findUserByName(userName);
        Book* b = findBookByName(bookName);

        if (!u) {
            std::cout << "User not found. Add user first.\n";
            return;
        }
        if (!b) {
            std::cout << "Book not found.\n";
            return;
        }

        if (!b->canBorrow()) {
            std::cout << "Sorry, no copies of '" << bookName << "' are available.\n";
            return;
        }

        if (u->hasBorrowed(bookName)) {
            std::cout << "User already has a copy of this book.\n";
            return;
        }

        b->borrow();
        u->borrowBook(bookName);
        std::cout << "Book borrowed successfully.\n";
    }

    void returnBook() {
        std::string userName, bookName;
        std::cout << "Enter user name: ";
        std::cin >> userName;
        std::cout << "Enter book name: ";
        std::cin >> bookName;

        User* u = findUserByName(userName);
        Book* b = findBookByName(bookName);

        if (!u || !b) {
            std::cout << "Invalid user or book name.\n";
            return;
        }

        if (!u->hasBorrowed(bookName)) {
            std::cout << "This user did not borrow this book.\n";
            return;
        }

        b->returnBook();
        u->returnBook(bookName);
        std::cout << "Book returned successfully.\n";
    }

    void printUsers() {
        if (users.empty()) {
            std::cout << "No users registered.\n";
            return;
        }

        std::cout << "\n" << std::left << std::setw(10) << "ID" << std::setw(20) << "Name" << "Borrowed Books\n";
        std::cout << std::string(50, '-') << "\n";
        for (const auto& u : users) {
            std::cout << std::left << std::setw(10) << u.getId() << std::setw(20) << u.getName();
            const auto& bList = u.getBorrowedBooks();
            if (bList.empty()) {
                std::cout << "[None]";
            } else {
                for (size_t i = 0; i < bList.size(); ++i) {
                    std::cout << bList[i] << (i == bList.size() - 1 ? "" : ", ");
                }
            }
            std::cout << "\n";
        }
    }

    void run() {
        while (true) {
            showMenu();
            int choice = getValidInt("Your choice: ", 1, 10);

            if (choice == 1) addBook();
            else if (choice == 2) searchBooksByPrefix();
            else if (choice == 3) printWhoBorrowedBook();
            else if (choice == 4) printLibrarySorted(true);
            else if (choice == 5) printLibrarySorted(false);
            else if (choice == 6) addUser();
            else if (choice == 7) borrowBook();
            else if (choice == 8) returnBook();
            else if (choice == 9) printUsers();
            else if (choice == 10) {
                std::cout << "Exiting system. Goodbye!\n";
                break;
            }
        }
    }
};

int main() {
    // Faster I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    LibraryManager library;
    library.run();

    return 0;
}
