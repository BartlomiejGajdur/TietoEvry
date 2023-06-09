#pragma once

#include <fstream>
#include <string>

#include "Player.hpp"

class FileManager {
public:
    explicit FileManager(const std::string& fileName) : fileName_(fileName) {}

    bool openFile();
    bool readFromFile();
    std::string getFileContent() const { return fileContent_; }
    static void SaveStatusToFile(const std::string& fileName, Map& mapa);
    static void ParseStatusFile(const std::string& fileName, Map& mapa);
    static void PerformActionsFromFile(const std::string& fileName, Map& mapa);
    static void printStatus(Map& map);
    ~FileManager();

private:
    std::string fileName_;
    std::string fileContent_;
    std::fstream file_;
};