#include <iostream>
#include <fstream>
#include <vector>
#include "Student.h"
#include "FileDatabase.h"
#include "Utils.h"

StudentManager::StudentManager(const std::string& studentsDbFilename)
    : studentsDb(studentsDbFilename) {}

int StudentManager::nextStudentPk() {
    return studentsDb.countRows() + 1;
}

bool StudentManager::registerStudent(const std::string& fullName, const std::string& studentNumber, int initialBalance) {
    int pk = nextStudentPk();

    std::string row = pk + "," + fullName + "," + studentNumber + "," + std::to_string(initialBalance);
    studentsDb.addRow(row);
    return true;
}

bool StudentManager::removeStudentByStudentNumber(const std::string& studentNumber) {
    std::ifstream file(studentsDb.getFilename());
    if (!file) {
        std::cerr << "Error opening student file.\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> columns = Utils::split(line, ',');
        if (columns.size() >= 2) { // Full name, Student Number, ...
            if (columns[1] == studentNumber) {
                std::string pk = columns[0]; // Assume pk is in column[0]
                file.close();
                
                return studentsDb.removeRow(pk); // Use existing removeRow
            }
        }
    }

    file.close();
    std::cerr << "Student with student number " << studentNumber << " not found.\n";
    return false;
}

bool StudentManager::depositBalance(const std::string& studentNumber, int amount) {
    std::vector<std::string> rows = studentsDb.searchByStudentNumber(studentNumber);

    if (rows.empty()) {
        return false; // Student not found
    }

    // Split the row
    std::vector<std::string> columns;
    std::string temp;
    for (char ch : rows[0]) {
        if (ch == ',') {
            columns.push_back(temp);
            temp.clear();
        } else {
            temp += ch;
        }
    }
    columns.push_back(temp);

    int currentBalance = std::stoi(columns[3]);
    currentBalance += amount;
    columns[3] = std::to_string(currentBalance);

    // Remove old row and add new row
    removeStudentByStudentNumber(studentNumber);
    std::string row = Utils::join(columns);
    studentsDb.addRow(row);
    return true;
}

std::vector<std::string> StudentManager::getStudent(const std::string& studentNumber) {
    return studentsDb.searchByStudentNumber(studentNumber);
}

bool StudentManager::editStudentInfo(const std::string& studentNumber, const std::string& newFullName) {
    std::vector<std::string> rows = studentsDb.searchByStudentNumber(studentNumber);

    if (rows.empty()) {
        return false; // Student not found
    }

    // Split the row
    std::vector<std::string> columns;
    std::string temp;
    for (char ch : rows[0]) {
        if (ch == ',') {
            columns.push_back(temp);
            temp.clear();
        } else {
            temp += ch;
        }
    }
    columns.push_back(temp);

    columns[1] = newFullName; // Update full name

    // Remove old row and add new row
    removeStudentByStudentNumber(studentNumber);
    std::string row = Utils::join(columns);
    studentsDb.addRow(row);
    return true;
}

bool StudentManager::deductBalance(const std::string& studentNumber, int amount) {
    std::vector<std::string> rows = studentsDb.searchByStudentNumber(studentNumber);

    if (rows.empty()) {
        return false; // Student not found
    }

    // Split the row
    std::vector<std::string> columns;
    std::string temp;
    for (char ch : rows[0]) {
        if (ch == ',') {
            columns.push_back(temp);
            temp.clear();
        } else {
            temp += ch;
        }
    }
    columns.push_back(temp);

    int currentBalance = std::stoi(columns[3]);
    if (currentBalance < amount) {
        return false; // Not enough balance
    }

    currentBalance -= amount;
    columns[3] = std::to_string(currentBalance);

    removeStudentByStudentNumber(studentNumber);
    std::string row = Utils::join(columns);
    studentsDb.addRow(row);
    return true;
}

bool StudentManager::hasEnoughBalance(const std::string& studentNumber, int price) {
    std::vector<std::string> rows = studentsDb.searchByStudentNumber(studentNumber);

    if (rows.empty()) {
        return false; // Student not found
    }

    // Split the row
    std::vector<std::string> columns;
    std::string temp;
    for (char ch : rows[0]) {
        if (ch == ',') {
            columns.push_back(temp);
            temp.clear();
        } else {
            temp += ch;
        }
    }
    columns.push_back(temp);

    int currentBalance = std::stoi(columns[3]);
    return currentBalance >= price;
}

void StudentManager::viewAllStudents() {
    std::ifstream file(studentsDb.getFilename());
    if (!file) {
        std::cerr << "Error opening student file.\n";
        return;
    }

    std::string line;
    std::cout << "\n--- All Students ---\n";
    while (std::getline(file, line)) {
        std::vector<std::string> columns = Utils::split(line, ',');
        if (columns.size() >= 3) { // Full name, student number, balance
            std::cout << "Name: " << columns[0] << ", Student Number: " << columns[1] << ", Balance: " << columns[2] << "\n";
        }
    }
    file.close();
}
