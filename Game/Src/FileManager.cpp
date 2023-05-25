#include <iostream>
#include <sstream> 

#include "../Include/FileManager.hpp"
#include "../Include/Units.hpp"
#include "../Include/Map.hpp"

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

void FileManager::SaveStatusToFile(const std::string& fileName, Map& mapa) {
  std::ofstream outputFile(fileName); 

  if (outputFile.is_open()) {
    outputFile<< mapa.getRound()<<"\n";
    outputFile<<"P "<<mapa.get_PlayerP()->getMoney()<<"\n";
    outputFile<<"E "<<mapa.get_PlayerE()->getMoney()<<"\n";

    for(const auto& unit : mapa.get_PlayerP()->getUnits()){
      outputFile<<"P "<<unit->getTypeInString()<<" "<<unit->getId()<<" "<<unit->getObjectCoordinates().getPositionX()<<" "<<unit->getObjectCoordinates().getPositionY()<<" "
      <<unit->getEndurance();
      if(auto dynamic = std::dynamic_pointer_cast<Base>(unit))
      {
        dynamic->getProduction().first != UnitTYPE::Base ? outputFile<<" "<<Unit::getUnitTypeInString(dynamic->getProduction().first)<<" "<<dynamic->getProduction().second<<"\n": outputFile<<" 0\n";  
      }else{
        outputFile<<"\n";
      }
      
    }

    for(const auto& unit : mapa.get_PlayerE()->getUnits()){
      outputFile<<"E "<<unit->getTypeInString()<<" "<<unit->getId()<<" "<<unit->getObjectCoordinates().getPositionX()<<" "<<unit->getObjectCoordinates().getPositionY()<<" "
      <<unit->getEndurance();
      if(auto dynamic = std::dynamic_pointer_cast<Base>(unit))
      {
        dynamic->getProduction().first != UnitTYPE::Base ? outputFile<<" "<<Unit::getUnitTypeInString(dynamic->getProduction().first)<<" "<<dynamic->getProduction().second<<"\n": outputFile<<" 0\n";  
      }else{
        outputFile<<"\n";
      }
    }
 
    outputFile.close(); 
    std::cout << "Status saved to file: " << fileName << std::endl;
  } else {
    std::cout << "Unable to open file: " << fileName << std::endl;
  }
}

void FileManager::ParseStatusFile(const std::string& fileName, Map& mapa) {
  std::ifstream inputFile(fileName);

  if (inputFile.is_open()) {
    std::string line;
    std::string playerTag;
    std::string unitType;
    int id, posX, posY, endurance;
    std::string productionType;
    int productionAmount;

    int playerPMoney = 0;
    int playerEMoney = 0;
    int roundNumber = 0;
    int lineCount = 0;

    while (std::getline(inputFile, line)) {
      std::istringstream iss(line);

      if (lineCount == 0) {
        if (iss >> roundNumber) {
          mapa.setRound(roundNumber);
          std::cout << "Round number: " << roundNumber << std::endl;
        }
      } else if (lineCount == 1) {
        if (iss >> playerTag) {
          if (playerTag == "P") {
            if (iss >> playerPMoney) {
              std::cout << "PlayerP money: " << playerPMoney << std::endl;
              mapa.get_PlayerP()->setMoney(playerPMoney);
            }
          } else if (playerTag == "E") {
            if (iss >> playerEMoney) {
              std::cout << "PlayerE money: " << playerEMoney << std::endl;
              mapa.get_PlayerE()->setMoney(playerEMoney);
            }
          }
        }
      } else {
        if (iss >> playerTag) {
          if (playerTag == "P" || playerTag == "E") {
            if (iss >> unitType >> id >> posX >> posY >> endurance) {
              if (playerTag == "P") {
                if (unitType == "B") {
                  if (iss >> productionType) { // czy to jest 0 np
                    if (productionType == "0") {
                      mapa.get_PlayerP()->addUnit(Unit::returnUnit(unitType, id, posX, posY, endurance, "B", 0));
                    } else if (iss >> productionAmount) {
                      mapa.get_PlayerP()->addUnit(Unit::returnUnit(unitType, id, posX, posY, endurance, productionType, productionAmount));
                    }
                  }
                } else {
                  mapa.get_PlayerP()->addUnit(Unit::returnUnit(unitType, id, posX, posY, endurance, "x", 0));
                }
                std::cout << "PlayerP unit: " << unitType << " ID: " << id << " Position: (" << posX << ", " << posY << ") Endurance: " << endurance << std::endl;
              } else if (playerTag == "E") {
                if (unitType == "B") {
                  if (iss >> productionType) { // czy to jest 0 np
                    if (productionType == "0") {
                      mapa.get_PlayerE()->addUnit(Unit::returnUnit(unitType, id, posX, posY, endurance, "B", 0));
                    } else if (iss >> productionAmount) {
                      mapa.get_PlayerE()->addUnit(Unit::returnUnit(unitType, id, posX, posY, endurance, productionType, productionAmount));
                    }
                  }
                } else {
                  mapa.get_PlayerE()->addUnit(Unit::returnUnit(unitType, id, posX, posY, endurance, "x", 0));
                }
                std::cout << "PlayerE unit: " << unitType << " ID: " << id << " Position: (" << posX << ", " << posY << ") Endurance: " << endurance << std::endl;
              }
            }
          }
        }
      }

      lineCount++;
    }

    inputFile.close();
  } else {
    std::cout << "Unable to open file: " << fileName << std::endl;
  }
}

