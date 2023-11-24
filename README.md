# Attendance-Management-System

The provided C++ code implements a simple Attendance Management System. This system allows users to manage student information, mark attendance, and save attendance records to a file. The structure of the program involves several classes and functions that work together to achieve these functionalities.

Code Structure:

CustomException (namespace MyNamespace):

This class inherits from std::exception and represents a custom exception. The what function is overridden to provide a custom exception message.
Person (abstract class):

Abstract class representing a person with a pure virtual function getName.
Derived classes (e.g., Student) will implement this function.
Student (derived from Person):

Represents a student with attributes such as name and roll number.
Implements the pure virtual function getName from the Person class.
Attendance:

Represents attendance records with information about the roll number and attendance status (Present/Absent).
AttendanceManager:

Manages a collection of persons (std::vector<std::unique_ptr<Person>>) and attendance records (std::vector<Attendance>).
Provides functions to read student information from a CSV file, mark attendance, save attendance records to a file, and print sorted attendance.
Uses static methods and demonstrates the usage of std::unique_ptr.
Main Function:

Prints a static message: Demonstrates the usage of a static method from AttendanceManager.

Creates an AttendanceManager object:

Reads student information from a CSV file ("students.csv").
Allows the user to mark attendance interactively and saves the attendance records to a file ("attendance.txt").
Prints sorted attendance records.
Prints information about each student using the printStudentInfo function.
Exception Handling:

Catches and handles custom exceptions from the MyNamespace namespace and standard exceptions, printing appropriate error messages.
