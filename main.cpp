#include <iostream>
#include <limits>
#include "libraries/Student.h"
#include "libraries/Reservation.h"
#include "libraries/DateTime.h"

void displayAdminMenu() {
    int choice;
    StudentManager studentManager("students.txt");
    Reservation reservationManager("foods.txt", "reservations.txt");

    while (true) {
        std::cout << "\n--- Admin Menu ---\n";
        std::cout << "1. Register a Student\n";
        std::cout << "2. Add a Food Item\n";
        std::cout << "3. View All Students\n";
        std::cout << "4. View All Foods\n";
        std::cout << "5. Assign Food to Student\n";
        std::cout << "6. Cancel Student's Reservation\n";
        std::cout << "7. View All Reservations\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";
        
        std::cin >> choice;
        
        // Input validation
        if (std::cin.fail()) {
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Invalid input. Please enter a number between 1 and 8.\n";
            continue;
        }

        switch (choice) {
            case 1:
                // Register a student
                {
                    std::string fullName, studentNumber;
                    int initialBalance;
                    std::cout << "Enter full name: ";
                    std::cin.ignore();  // to clear the buffer
                    std::getline(std::cin, fullName);
                    std::cout << "Enter student number: ";
                    std::cin >> studentNumber;
                    std::cout << "Enter initial balance: ";
                    std::cin >> initialBalance;
                    studentManager.registerStudent(fullName, studentNumber, initialBalance);
                    std::cout << "Student registered successfully.\n";
                }
                break;

            case 2:
                // Add a food item
                {
                    std::string foodName, mealType, date;
                    int price, capacity;
                    std::cout << "Enter food name: ";
                    std::cin.ignore();
                    std::getline(std::cin, foodName);
                    std::cout << "Enter meal type (lunch/dinner): ";
                    std::cin >> mealType;
                    std::cout << "Enter date (YYYY-MM-DD): ";
                    std::cin >> date;
                    std::cout << "Enter food price: ";
                    std::cin >> price;
                    std::cout << "Enter food capacity: ";
                    std::cin >> capacity;

                    reservationManager.addFoodForDay(date, mealType, foodName, price, capacity);
                    std::cout << "Food item added successfully.\n";
                }
                break;

            case 3:
                // View all students
                studentManager.viewAllStudents();
                break;

            case 4:
                // View all food items
                reservationManager.viewAllFoods();
                break;

            case 5:
                // Assign food to student
                {
                    std::string studentNumber, mealType, date, foodName;
                    std::cout << "Enter student number: ";
                    std::cin >> studentNumber;
                    std::cout << "Enter meal type (lunch/dinner): ";
                    std::cin >> mealType;
                    std::cout << "Enter food name:";
                    std::cin >> foodName;
                    std::cout << "Enter date (YYYY-MM-DD): ";
                    std::cin >> date;
                    bool result = reservationManager.reserveFood(studentNumber, foodName, date, mealType);
                    if (result) {
                        std::cout << "Reservation successful.\n";
                    } else {
                        std::cout << "Reservation failed. Either food is unavailable or balance is insufficient.\n";
                    }
                }
                break;

            case 6:
                // Cancel reservation
                {
                    std::string studentNumber, mealType, date;
                    std::cout << "Enter student number: ";
                    std::cin >> studentNumber;
                    std::cout << "Enter date (YYYY-MM-DD): ";
                    std::cin >> date;
                    bool result = reservationManager.cancelReservation(studentNumber, date);
                    if (result) {
                        std::cout << "Reservation canceled and balance refunded.\n";
                    } else {
                        std::cout << "Cancellation failed. Reservation not found.\n";
                    }
                }
                break;

            case 7:
                // View all reservations
                reservationManager.viewAllFoods();
                break;

            case 8:
                // Exit
                std::cout << "Exiting admin menu...\n";
                return; // Exit the loop and program

            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    displayAdminMenu();
    return 0;
}

