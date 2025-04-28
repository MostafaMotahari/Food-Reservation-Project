// Utils.h
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

class Utils {
public:
    // Joins elements of a vector into a single string separated by a delimiter
    static std::string join(const std::vector<std::string>& elements, const std::string& delimiter = ",");
    static std::vector<std::string> split(const std::string& s, char delimiter);
};

#endif // UTILS_H

