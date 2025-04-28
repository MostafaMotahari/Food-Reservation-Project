#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
#include <vector>
#include "FileDatabase.h"

class Reservation {
private:
    FileDatabase foodsDb;
    FileDatabase reservationsDb;
    int nextReservationPk();

public:
    Reservation(const std::string& foodsFile, const std::string& reservationsFile);

    void addFoodForDay(const std::string& date, const std::string& mealType, const std::string& foodName, int price, int capacity);
    std::vector<std::string> getFoodsForDay(const std::string& date);

    bool reserveFood(const std::string& studentNumber, const std::string& foodName, const std::string& date, const std::string& mealType);
    bool cancelReservation(const std::string& studentNumber, const std::string& date);
    std::vector<std::string> getReservationsForStudent(const std::string& studentNumber);
    void viewAllFoods();
};

#endif

