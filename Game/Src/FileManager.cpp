#include <iostream>

#include "../Include/FileManager.hpp"
#include "../Include/Units.hpp"

FileManager::~FileManager() {
  if (file_.is_open())
    file_.close();
}

bool FileManager::openFile() {
  file_.open(fileName_);

  if (!file_.is_open()) {
    std::cerr << "Error while file opening: " << fileName_ << "\n";
    return false;
  }

  return true;
}

bool FileManager::readFromFile() {
  if (!file_.is_open()) {
    std::cerr << "File is not open: " << fileName_ << "\n";
    return false;
  }
  std::string line{};

  while (file_ >> line)
    fileContent_ += line + "\n";

  return true;
}

#include <fstream>

void FileManager::SaveStatusToFile(const std::string& fileName, std::shared_ptr<Player> PlayerP_, std::shared_ptr<Player> PlayerE_) {
  std::ofstream outputFile(fileName); // Tworzenie strumienia wyjściowego

  if (outputFile.is_open()) {
    outputFile<<"P "<<PlayerP_->getMoney()<<"\n";
    outputFile<<"E "<<PlayerE_->getMoney()<<"\n";

    for(const auto& unit : PlayerP_->getUnits()){
      outputFile<<"P "<<unit->getTypeInString()<<" "<<unit->getId()<<" "<<unit->getObjectCoordinates().getPositionX()<<" "<<unit->getObjectCoordinates().getPositionY()<<" "
      <<unit->getEndurance();
      if(auto dynamic = std::dynamic_pointer_cast<Base>(unit))
      {
        dynamic->getProduction().first != UnitTYPE::Base ? outputFile<<" "<<Unit::getUnitTypeInString(dynamic->getProduction().first)<<"\n": outputFile<<" 0\n";  
      }else{
        outputFile<<"\n";
      }
      
    }

    for(const auto& unit : PlayerE_->getUnits()){
      outputFile<<"E "<<unit->getTypeInString()<<" "<<unit->getId()<<" "<<unit->getObjectCoordinates().getPositionX()<<" "<<unit->getObjectCoordinates().getPositionY()<<" "
      <<unit->getEndurance();
      if(auto dynamic = std::dynamic_pointer_cast<Base>(unit))
      {
         dynamic->getProduction().first != UnitTYPE::Base ? outputFile<<" "<<Unit::getUnitTypeInString(dynamic->getProduction().first)<<"\n": outputFile<<" 0\n";   
      }else{
        outputFile<<"\n";
      }
    }
 
    outputFile.close(); // Zamknięcie strumienia
    std::cout << "Status saved to file: " << fileName << std::endl;
  } else {
    std::cout << "Unable to open file: " << fileName << std::endl;
  }
}
