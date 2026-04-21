# Library Management System

A comprehensive, object-oriented C++ application designed to manage library operations, including book inventory tracking, user registration, and borrowing/returning workflows.

## 🚀 Key Features

* **Advanced Inventory Tracking:** Manage books with unique IDs, names, and quantities.
* **Flexible Searching:** Search for books quickly using a prefix-based search system.
* **Borrowing & Returning System:** Robust logic to handle book issues and returns, ensuring stock levels are updated in real-time.
* **User Management:** Register users and track their borrowing history.
* **Detailed Reporting:**
    * View library inventory sorted by **Book ID**.
    * View library inventory sorted by **Book Name**.
    * List all registered users and their currently borrowed books.
    * Identify which users have borrowed a specific book.
* **Smart Validation:** Prevents borrowing unavailable books or returning books not currently held by a user.

## 🛠 Technical Highlights

The system is implemented using clean **C++11** and adheres to high-quality software design patterns:
* **Object-Oriented Design (OOD):** Modular architecture with `Book`, `User`, and `LibraryManager` classes.
* **STL Power:** Extensive use of `std::vector`, `std::string`, and `std::algorithm` (like `std::sort` and `std::find`) for efficient data manipulation.
* **Data Integrity:** Input validation mechanisms to handle invalid menu choices and non-integer inputs.
* **Efficient Searching:** Optimized lookups for users and books within the system's memory.

## 📋 How to Run

1.  **Compile the source code:**
    ```bash
    g++ -o LibrarySystem Library-System.cpp
    ```

2.  **Run the application:**
    ```bash
    ./LibrarySystem
    ```

## 📖 System Operations

* **Add Book/User:** Expand the library's database with new resources and members.
* **Borrow Book:** Facilitates the transaction between a user and the library inventory.
* **Search/Prefix Search:** Quickly locate specific books without typing full titles.
* **Print Library/Users:** Generate formatted reports to monitor the status of the entire system.

---
**This project serves as a demonstration of C++ proficiency, focusing on memory management, class relationships, and algorithmic sorting.**
