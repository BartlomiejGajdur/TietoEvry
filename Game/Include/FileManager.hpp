#pragma once

#include <fstream>
#include <string>

class FileManager {
public:
  FileManager(const std::string fileName) : fileName_(fileName){};

  bool openFile();
  bool readFromFile();
  std::string getFileContent() const { return fileContent_; };
 
  ~FileManager();

private:
  std::string fileName_;
  std::string fileContent_;
  std::fstream file_;
};