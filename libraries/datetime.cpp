#include "DateTime.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

DateTime::DateTime() {
    timestamp = std::time(nullptr);
}

DateTime::DateTime(std::time_t timestamp) {
    this->timestamp = timestamp;
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second) {
    std::tm tm_time = {};
    tm_time.tm_year = year - 1900; // tm_year is years since 1900
    tm_time.tm_mon = month - 1;    // tm_mon is 0-11
    tm_time.tm_mday = day;
    tm_time.tm_hour = hour;
    tm_time.tm_min = minute;
    tm_time.tm_sec = second;
    timestamp = std::mktime(&tm_time);
}

DateTime DateTime::now() {
    return DateTime();
}

DateTime DateTime::daysLater(int days) {
    std::time_t now = std::time(nullptr);
    return DateTime(now + (days * 24 * 60 * 60));
}

bool DateTime::operator<(const DateTime& other) const {
    return timestamp < other.timestamp;
}

bool DateTime::operator>(const DateTime& other) const {
    return timestamp > other.timestamp;
}

bool DateTime::operator==(const DateTime& other) const {
    return timestamp == other.timestamp;
}

std::string DateTime::toString() const {
    std::tm* tm_info = std::localtime(&timestamp);
    std::ostringstream oss;
    oss << std::put_time(tm_info, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

static std::vector<std::string> getNextNDates(int n) {
    std::vector<std::string> dates;

    time_t now = time(0);
    tm* ltm = localtime(&now);

    for (int i = 0; i < n; ++i) {
        tm futureDate = *ltm;
        futureDate.tm_mday += i;

        mktime(&futureDate); // Normalize the date

        char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", &futureDate);
        dates.push_back(std::string(buffer));
    }

    return dates;
}
