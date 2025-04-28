#include "FileDatabase.h"
#include "DateTime.h" // For getting current datetime
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

FileDatabase::FileDatabase(const std::string& filename) {
    this->filename = filename;
}

void FileDatabase::addRow(const std::string& row) {
    std::ofstream file(filename, std::ios::app); // append mode
    if (file.is_open()) {
        file << row << "\n";
        file.close();
    }
}

std::string FileDatabase::searchByPK(const std::string& pk) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> columns = Utils::split(line, ',');
        if (columns.size() > 0 && columns[0] == pk) {
            return line; // found
        }
    }
    return ""; // not found
}

bool FileDatabase::removeRow(const std::string& pk) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::vector<std::string> rows;
    std::string line;
    bool found = false;

    while (std::getline(file, line)) {
        std::vector<std::string> columns = Utils::split(line, ',');
        if (columns.size() > 0 && columns[0] == pk) {
            found = true; // found the row, skip it
            continue;
        }
        rows.push_back(line); // keep other rows
    }
    file.close();

    if (!found) {
        return false; // not found
    }

    std::ofstream outfile(filename, std::ios::trunc); // truncate file
    for (const auto& row : rows) {
        outfile << row << "\n";
    }
    outfile.close();
    return true;
}

bool FileDatabase::updateRow(const std::string& pk, const std::string& newRow) {
    bool removed = removeRow(pk);
    if (!removed) {
        return false; // can't update non-existing row
    }
    addRow(newRow);
    return true;
}

std::vector<std::string> FileDatabase::searchByStudentNumber(const std::string& studentNumber) {
    std::ifstream file(filename);
    std::vector<std::string> results;

    if (!file.is_open()) {
        return results;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> columns = Utils::split(line, ',');
        if (columns.size() > 2 && columns[2] == studentNumber) {
            results.push_back(line);
        }
    }
    return results;
}

std::vector<std::string> FileDatabase::searchByFullName(const std::string& fullName) {
    std::ifstream file(filename);
    std::vector<std::string> results;

    if (!file.is_open()) {
        return results;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> columns = Utils::split(line, ',');
        if (columns.size() > 1 && columns[1] == fullName) {
            results.push_back(line);
        }
    }
    return results;
}

std::string FileDatabase::getFilename() {
    return filename;
}

int FileDatabase::countRows() {
    std::ifstream file(filename);
    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            count++;
        }
    }
    file.close();
    return count;
}
