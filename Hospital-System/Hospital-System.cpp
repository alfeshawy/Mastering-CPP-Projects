#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <limits>
#include <iomanip>

/**
 * @enum PatientStatus
 * @brief Represents the priority level of a patient.
 */
enum class PatientStatus {
    REGULAR = 0,
    URGENT = 1
};

/**
 * @class Patient
 * @brief Holds basic information about a patient.
 */
class Patient {
private:
    std::string name;
    PatientStatus status;

public:
    Patient(std::string n, PatientStatus s) : name(n), status(s) {}

    std::string getName() const { return name; }
    PatientStatus getStatus() const { return status; }
    
    std::string getStatusString() const {
        return (status == PatientStatus::URGENT) ? "Urgent" : "Regular";
    }
};

/**
 * @class Specialization
 * @brief Manages a queue of patients for a specific medical specialization.
 */
class Specialization {
private:
    static constexpr int MAX_QUEUE_SIZE = 5;
    std::deque<Patient> patients;
    int id;

public:
    explicit Specialization(int specializationId) : id(specializationId) {}

    bool isFull() const {
        return patients.size() >= MAX_QUEUE_SIZE;
    }

    bool isEmpty() const {
        return patients.empty();
    }

    bool addPatient(const std::string& name, PatientStatus status) {
        if (isFull()) {
            return false;
        }

        if (status == PatientStatus::URGENT) {
            patients.push_front(Patient(name, status));
        } else {
            patients.push_back(Patient(name, status));
        }
        return true;
    }

    Patient getNextPatient() {
        if (isEmpty()) {
            throw std::runtime_error("No patients in queue.");
        }
        Patient next = patients.front();
        patients.pop_front();
        return next;
    }

    void printQueue() const {
        if (isEmpty()) return;

        std::cout << "\n******************************************\n";
        std::cout << " Specialization " << std::setw(2) << id << ": " << patients.size() << " patient(s)\n";
        std::cout << "******************************************\n";
        
        int count = 1;
        for (const auto& patient : patients) {
            std::cout << " " << count++ << ". " << std::left << std::setw(15) << patient.getName() 
                      << " [" << patient.getStatusString() << "]\n";
        }
    }

    int getPatientCount() const {
        return static_cast<int>(patients.size());
    }
};

/**
 * @class HospitalManager
 * @brief Orchestrates the entire hospital system operations.
 */
class HospitalManager {
private:
    static constexpr int MAX_SPECIALIZATIONS = 20;
    std::vector<Specialization> specializations;

    // Helper for input validation
    int getValidInt(const std::string& prompt, int min, int max) {
        int val;
        while (true) {
            std::cout << prompt;
            if (std::cin >> val && val >= min && val <= max) {
                return val;
            }
            std::cout << "Invalid input! Please enter a number between " << min << " and " << max << ".\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

public:
    HospitalManager() {
        for (int i = 1; i <= MAX_SPECIALIZATIONS; ++i) {
            specializations.emplace_back(i);
        }
    }

    void showMenu() {
        std::cout << "\n==========================================\n";
        std::cout << "        HOSPITAL MANAGEMENT SYSTEM        \n";
        std::cout << "==========================================\n";
        std::cout << " 1) Add a new patient\n";
        std::cout << " 2) Print all patients\n";
        std::cout << " 3) Get next patient\n";
        std::cout << " 4) Exit\n";
        std::cout << "------------------------------------------\n";
    }

    void addPatient() {
        int specId = getValidInt("Enter specialization (1-20): ", 1, 20);
        
        std::string name;
        std::cout << "Enter patient name: ";
        std::cin >> name;

        int statusInt = getValidInt("Enter status (0 for Regular, 1 for Urgent): ", 0, 1);
        PatientStatus status = static_cast<PatientStatus>(statusInt);

        if (specializations[specId - 1].addPatient(name, status)) {
            std::cout << "Patient added successfully.\n";
        } else {
            std::cout << "Sorry, the queue for this specialization is full.\n";
        }
    }

    void printAllPatients() {
        bool anyPatients = false;
        for (const auto& spec : specializations) {
            if (!spec.isEmpty()) {
                spec.printQueue();
                anyPatients = true;
            }
        }
        if (!anyPatients) {
            std::cout << "\nNo patients are currently in any queue.\n";
        }
    }

    void processNextPatient() {
        int specId = getValidInt("Enter specialization (1-20): ", 1, 20);
        
        try {
            Patient p = specializations[specId - 1].getNextPatient();
            std::cout << "\n>>> Please go with the doctor, " << p.getName() << " <<<\n";
        } catch (const std::exception& e) {
            std::cout << "\nThere are no patients in this specialization.\n";
        }
    }

    void run() {
        while (true) {
            showMenu();
            int choice = getValidInt("Your choice: ", 1, 4);

            if (choice == 1) addPatient();
            else if (choice == 2) printAllPatients();
            else if (choice == 3) processNextPatient();
            else {
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

    HospitalManager hospital;
    hospital.run();

    return 0;
}
