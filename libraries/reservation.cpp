#include "Reservation.h"
#include "Student.h"
#include "DateTime.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <vector>

Reservation::Reservation(const std::string& foodsFile, const std::string& reservationsFile)
    : foodsDb(foodsFile), reservationsDb(reservationsFile) {}

void Reservation::addFoodForDay(const std::string& date, const std::string& mealType, const std::string& foodName, int price, int capacity) {
    // Generate a simple PK: foodName_date_mealType
    std::string pk = foodName + "_" + date + "_" + mealType;

    std::string row = pk + "," + foodName + "," + std::to_string(price) + "," + date + "," + mealType + "," + std::to_string(capacity);
    foodsDb.addRow(row);
}

std::vector<std::string> Reservation::getFoodsForDay(const std::string& date) {
    std::ifstream file(foodsDb.getFilename());
    std::vector<std::string> foods;

    if (!file.is_open()) {
        return foods;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> columns = Utils::split(line, ',');
        if (columns.size() > 3 && columns[3] == date) { // Date is column 4 (index 3)
            foods.push_back(line);
        }
    }
    return foods;
}


bool Reservation::reserveFood(const std::string& studentNumber, const std::string& foodName, const std::string& date, const std::string& mealType) {
    std::ifstream file(foodsDb.getFilename());
    if (!file.is_open()) {
        return false;
    }

    std::string foundFoodLine;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> columns = Utils::split(line, ',');
        if (columns.size() >= 5 && columns[1] == foodName && columns[3] == date && columns[4] == mealType) {
            foundFoodLine = line;
            break;
        }
    }
    file.close();

    if (foundFoodLine.empty()) {
        // Food not found
        return false;
    }

    std::vector<std::string> foodColumns = Utils::split(foundFoodLine, ',');
    std::string foodPk = foodColumns[0];
    std::string price = foodColumns[2];

    int capacity = std::stoi(foodColumns[5]);
    if (capacity <= 0) {
        return false; // No capacity left
    }
    capacity -= 1;
    foodColumns[5] = std::to_string(capacity);

    // User balance deduction
    StudentManager studentManager("students.txt");
    if (!studentManager.deductBalance(studentNumber, std::stoi(price))) {
        return false;
    }

    int newPk = nextReservationPk();

    std::string reservationDatetime = DateTime::now().toString();
    std::string receiveDatetime = date;

    if (mealType == "Lunch") {
        receiveDatetime += " 12:30:00";
    } else {
        receiveDatetime += " 18:30:00";
    }

    std::string reservationRow = std::to_string(newPk) + "," + "student" + "," + studentNumber + "," + foodName + "," + price + "," + mealType + "," + reservationDatetime + "," + receiveDatetime;

    reservationsDb.addRow(reservationRow);

    foodsDb.removeRow(foodColumns[0]); // PK is column 0
    std::string row = Utils::join(foodColumns);
    foodsDb.addRow(row);
    return true;
}

int Reservation::nextReservationPk() {
    std::ifstream file(reservationsDb.getFilename());
    if (!file.is_open()) {
        return 1; // Start from 1
    }

    int maxPk = 0;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> columns = Utils::split(line, ',');
        if (!columns.empty()) {
            int currentPk = std::stoi(columns[0]);
            if (currentPk > maxPk) {
                maxPk = currentPk;
            }
        }
    }
    file.close();
    return maxPk + 1;
}

bool Reservation::cancelReservation(const std::string& studentNumber, const std::string& date) {

    std::ifstream file(reservationsDb.getFilename());
    if (!file) {
        std::cerr << "Error opening reservation database.\n";
        return false;
    }

    std::string line;
    std::string targetPk = "";
    std::vector<std::string> reservationColumns;
    
    while (std::getline(file, line)) {
        reservationColumns = Utils::split(line, ',');
        if (reservationColumns.size() >= 8) { // pk, fullname, student number, food, price, meal, reservation datetime, receive datetime
            if (reservationColumns[2] == studentNumber && reservationColumns[6].substr(0, 10) == date) {
                targetPk = reservationColumns[0]; // found the PK
                break;
            }
        }
    }
    file.close();

    if (targetPk.empty()) {
        std::cout << "No reservation found for student " << studentNumber << " on " << date <<".\n";
        return false;
    }

    std::vector<std::string> foods = getFoodsForDay(date);
    if (foods.empty()) {
        return false; // Food not found
    }

    std::vector<std::string> columns;
    std::string temp;
    for (char ch : foods[0]) {
        if (ch == ',') {
            columns.push_back(temp);
            temp.clear();
        } else {
            temp += ch;
        }
    }
    columns.push_back(temp);
    // Increase food capacity
    int capacity = std::stoi(columns[5]);
    capacity += 1;
    columns[5] = std::to_string(capacity);

    foodsDb.removeRow(columns[0]); // Remove old food row by PK
    std::string row = Utils::join(columns);
    foodsDb.addRow(row);          // Add updated food row
 
    StudentManager studentManager("students.txt");
    int price = std::stoi(columns[2]);
    studentManager.depositBalance(studentNumber, price);

    return reservationsDb.removeRow(targetPk);
}

std::vector<std::string> Reservation::getReservationsForStudent(const std::string& studentNumber) {
    return reservationsDb.searchByStudentNumber(studentNumber);
}

void Reservation::viewAllFoods() {
    std::ifstream file(foodsDb.getFilename());
    if (!file) {
        std::cerr << "Error opening food file.\n";
        return;
    }

    std::string line;
    std::cout << "\n--- All Foods ---\n";
    while (std::getline(file, line)) {
        std::vector<std::string> columns = Utils::split(line, ',');
        if (columns.size() >= 6) { // PK, food name, price, meal type, date, capacity
            std::cout << "Food: " << columns[1] << ", Price: " << columns[2] << ", Meal Type: " << columns[3]
                      << ", Date: " << columns[4] << ", Capacity: " << columns[5] << "\n";
        }
    }
    file.close();
}
