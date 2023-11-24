#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

#define CXX_STD 11

namespace MyNamespace {
    class CustomException : public std::exception {
    public:
        const char* what() const noexcept(true) override;
    };
}

inline const char* MyNamespace::CustomException::what() const noexcept(true) {
    return "Custom exception occurred.";
}

class Student;

class Person {
public:
    virtual std::string getName() const = 0;
    virtual ~Person() = default;

    friend void printStudentInfo(const Student& student);
};

class Student : public Person {
private:
    std::string name;
    int rollNumber;

public:
    Student(const std::string& studentName, int studentRollNumber)
        : name(studentName), rollNumber(studentRollNumber) {}

    std::string getName() const override {
        return name;
    }

    int getRollNumber() const {
        return rollNumber;
    }

    friend void printStudentInfo(const Student& student);
};

void printStudentInfo(const Student& student) {
    std::cout << "Student Name: " << student.getName() << ", Roll Number: " << student.getRollNumber() << std::endl;
}

class Attendance {
private:
    int rollNumber;
    char status;

public:
    Attendance(int studentRollNumber, char attendanceStatus)
        : rollNumber(studentRollNumber), status(attendanceStatus) {}

    int getRollNumber() const {
        return rollNumber;
    }

    char getStatus() const {
        return status;
    }
};

class AttendanceManager {
private:
    std::vector<std::unique_ptr<Person>> persons;
    std::vector<Attendance> attendanceRecords;

public:
    void readStudentsFromCSV(const std::string& filename);

    void markAttendance();

    void saveAttendanceToFile(const std::string& filename);

    static void printMessage() {
        std::cout << "This is a static method.\n";
    }

    const std::vector<Attendance>& getAttendanceRecords() const {
        return attendanceRecords;
    }

    const std::vector<std::unique_ptr<Person>>& getStudents() const {
        return persons;
    }

    void printSortedAttendance() const {
        auto compareByRollNumber = [](const Attendance& a, const Attendance& b) {
            return a.getRollNumber() < b.getRollNumber();
        };

        std::vector<Attendance> sortedAttendance = attendanceRecords;
        std::sort(sortedAttendance.begin(), sortedAttendance.end(), compareByRollNumber);

        for (const auto& record : sortedAttendance) {
            std::cout << "Roll Number: " << record.getRollNumber() << ", Status: " << record.getStatus() << std::endl;
        }
    }
};

void AttendanceManager::readStudentsFromCSV(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw MyNamespace::CustomException();
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        int rollNumber;

        if (iss >> name >> rollNumber) {
            persons.push_back(std::unique_ptr<Student>(new Student(name, rollNumber)));
        }
    }

    file.close();
}

void AttendanceManager::markAttendance() {
    for (const auto& person : persons) {
        auto student = dynamic_cast<Student*>(person.get());
        if (student) {
            int rollNumber = student->getRollNumber();
            char status;

            std::cout << "Mark attendance for Roll Number " << rollNumber << " (P for Present, A for Absent): ";
            std::cin >> status;

            if (status == 'P' || status == 'p' || status == 'A' || status == 'a') {
                attendanceRecords.emplace_back(rollNumber, std::toupper(status));
                std::cout << "Attendance marked successfully.\n";
            } else {
                std::cout << "Invalid attendance status. Please enter 'P' or 'A'.\n";
            }
        }
    }
}

void AttendanceManager::saveAttendanceToFile(const std::string& filename) {
    std::ofstream file(filename.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Unable to create or open file");
    }

    for (const auto& record : attendanceRecords) {
        file << record.getRollNumber() << " " << record.getStatus() << std::endl;
    }

    file.close();
}

void printAttendance(const AttendanceManager& manager) {
    for (const auto& record : manager.getAttendanceRecords()) {
        std::cout << "Roll Number: " << record.getRollNumber() << ", Status: " << record.getStatus() << std::endl;
    }
}

int main() {
    try {
        AttendanceManager::printMessage();

        AttendanceManager attendanceManager;
        attendanceManager.readStudentsFromCSV("students.csv");

        attendanceManager.markAttendance();

        attendanceManager.saveAttendanceToFile("attendance.txt");

        attendanceManager.printSortedAttendance();

        for (const auto& personPtr : attendanceManager.getStudents()) {
            const Student* student = dynamic_cast<const Student*>(personPtr.get());
            if (student) {
                printStudentInfo(*student);
            }
        }

    } catch (const MyNamespace::CustomException& ce) {
        std::cerr << "Custom Exception: " << ce.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}