# Hospital Management System

A robust, object-oriented C++ application designed to streamline patient intake and queue management across multiple medical departments.

## 🚀 Key Features

* **Multi-Specialization Management:** Supports up to 20 distinct medical departments simultaneously.
* **Smart Priority Queueing:** Automatically prioritizes **Urgent** cases by placing them at the front of the queue, while **Regular** cases follow a standard FIFO (First-In-First-Out) order.
* **Capacity Control:** Strict enforcement of a 5-patient limit per specialization to maintain operational efficiency.
* **Input Validation:** Built-in error handling to ensure data integrity and prevent system crashes from invalid user inputs.
* **Performance Optimized:** Utilizes `std::deque` to achieve $O(1)$ time complexity for additions and removals at both ends of the queue.

## 🛠 Technical Highlights

The project is built using modern **C++11** standards and focuses on core Software Engineering principles:
* **Encapsulation:** All patient and queue logic is securely managed within class boundaries.
* **STL Integration:** Efficient use of `std::vector` for specialization storage and `std::deque` for dynamic patient handling.
* **Clean Code:** Implementation of `enum class` for type-safety and descriptive naming conventions for high maintainability.

## 📋 How to Run

1. **Compile the code:**
   ```bash
   g++ -o HospitalSystem Hospital-System.cpp
