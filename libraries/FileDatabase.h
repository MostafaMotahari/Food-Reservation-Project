#ifndef FILEDATABASE_H
#define FILEDATABASE_H

#include <string>
#include <vector>

class FileDatabase {
private:
    std::string filename;

public:
    FileDatabase(const std::string& filename);

    void addRow(const std::string& row);
    bool removeRow(const std::string& pk);
    std::string searchByPK(const std::string& pk);
    std::vector<std::string> searchByStudentNumber(const std::string& studentNumber);
    std::vector<std::string> searchByFullName(const std::string& fullName);
    bool updateRow(const std::string& pk, const std::string& newRow);
    std::string getFilename();
    int countRows();
};

#endif

