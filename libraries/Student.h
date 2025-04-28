#pragma once
#include <string>
#include <vector>
#include "FileDatabase.h"

class StudentManager {
private:
    FileDatabase studentsDb;

    int nextStudentPk();

public:
    StudentManager(const std::string& studentsDbFilename);

    bool registerStudent(const std::string& fullName, const std::string& studentNumber, int initialBalance);
    bool depositBalance(const std::string& studentNumber, int amount);
    std::vector<std::string> getStudent(const std::string& studentNumber);
    bool editStudentInfo(const std::string& studentNumber, const std::string& newFullName);
    bool deductBalance(const std::string& studentNumber, int amount);
    bool hasEnoughBalance(const std::string& studentNumber, int price);
    bool removeStudentByStudentNumber(const std::string& studentNumber);
    void viewAllStudents();
};

