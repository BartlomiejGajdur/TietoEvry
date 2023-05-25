#pragma once

#include <fstream>
#include <string>

#include "Player.hpp"

class FileManager {
public:
  FileManager(const std::string fileName) : fileName_(fileName){};

  bool openFile();
  bool readFromFile();
  std::string getFileContent() const { return fileContent_; };
  static void SaveStatusToFile(const std::string& fileName, std::shared_ptr<Player> PlayerP_, std::shared_ptr<Player> PlayerE_);
  static void ParseStatusFile(const std::string& fileName, std::shared_ptr<Player> PlayerP_, std::shared_ptr<Player> PlayerE_);
  ~FileManager();

private:
  std::string fileName_;
  std::string fileContent_;
  std::fstream file_;
};