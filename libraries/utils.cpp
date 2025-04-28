// Utils.cpp
#include "Utils.h"

std::string Utils::join(const std::vector<std::string>& elements, const std::string& delimiter) {
    if (elements.empty()) {
        return "";
    }

    std::string result = elements[0];
    for (size_t i = 1; i < elements.size(); ++i) {
        result += delimiter + elements[i];
    }
    return result;
}

std::vector<std::string> Utils::split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    
    for (char ch : s) {
        if (ch == delimiter) {
            tokens.push_back(token);
            token.clear();
        } else {
            token += ch;
        }
    }
    tokens.push_back(token); // push the last token
    return tokens;
}

