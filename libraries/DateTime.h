#ifndef DATETIME_H
#define DATETIME_H

#include <ctime>
#include <string>
#include <vector>

class DateTime {
private:
    std::time_t timestamp; // Internally store time as a timestamp (seconds since 1970)

public:
    DateTime();                               // Default: current time
    DateTime(std::time_t timestamp);
    DateTime(int year, int month, int day, int hour, int minute, int second); // Specific time

    static DateTime now();                    // Get current time
    static DateTime daysLater(int days);       // Get time + N days

    bool operator<(const DateTime& other) const;
    bool operator>(const DateTime& other) const;
    bool operator==(const DateTime& other) const;

    std::string toString() const;              // Format to string
    static std::vector<std::string> getNextNDates(int n);
};

#endif
