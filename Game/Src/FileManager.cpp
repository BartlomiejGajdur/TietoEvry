#include <iostream>
#include <sstream> 

#include "../Include/FileManager.hpp"
#include "../Include/Units.hpp"
#include "../Include/Map.hpp"
#include "../Include/Mediator.hpp"

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
          
        }
      } else if (lineCount == 1) {
        if (iss >> playerTag) {
          if (playerTag == "P") {
            if (iss >> playerPMoney) {
              
              mapa.get_PlayerP()->setMoney(playerPMoney);
            }
          } else if (playerTag == "E") {
            if (iss >> playerEMoney) {
              
              mapa.get_PlayerE()->setMoney(playerEMoney);
            }
          }
        }
      } else if(lineCount == 2){
        if (iss >> playerTag) {
          if (playerTag == "P") {
            if (iss >> playerPMoney) {
              
              mapa.get_PlayerP()->setMoney(playerPMoney);
            }
          } else if (playerTag == "E") {
            if (iss >> playerEMoney) {
              
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

void FileManager::PerformActionsFromFile(const std::string& fileName, Map& mapa) {
    std::ifstream inputFile(fileName);

    if (inputFile.is_open()) {
        std::string line;
        std::string actionType;
        std::string unitType;
        int id, posX, posY;
        int id_2;
        switch (mapa.getRound() % 2)
        {
        case 0:
          while (std::getline(inputFile, line)) {
            std::istringstream iss(line);

            if (iss >> id >> actionType) {
                if (actionType == "A") {
                  if (iss >> id_2)
                    mapa.AttackAction_PlayerP(id, id_2);
                } else if (actionType == "M") {
                    if(iss>>posX >> posY)
                      mapa.MoveAction_PlayerP(id, Coordinates{posX,posY});
                } else if (actionType == "B") {
                    if(iss>>unitType)
                      mapa.ProductAction_PlayerP(Unit::getUnitTypeFromString(unitType));
                } else {
                    std::cout << "Unknown unit type: " << actionType << std::endl;
                }
            }
        }
          break;

        case 1:
          while (std::getline(inputFile, line)) {
            std::istringstream iss(line);

            if (iss >> id >> actionType) {
                if (actionType == "A") {
                  if (iss >> id_2)
                    mapa.AttackAction_PlayerE(id, id_2);
                } else if (actionType == "M") {
                    if(iss>>posX >> posY)
                      mapa.MoveAction_PlayerE(id, Coordinates{posX,posY});
                } else if (actionType == "B") {
                    if(iss>>unitType)
                      mapa.ProductAction_PlayerE(Unit::getUnitTypeFromString(unitType));
                } else {
                    std::cout << "Unknown unit type: " << actionType << std::endl;
                }
            }
        }
          
          break;
        
        default:
          break;
        }
        

        inputFile.close();
    } else {
        std::cout << "Unable to open file: " << fileName << std::endl;
    }
}

void FileManager::printStatus(Map& map){
  std::cout<<"Round Number: "<<map.getRound()<<"\nPrepare the "<<ActionsFile<<" for player ";
  map.getRound() % 2 == 0 ? std::cout<<" [E] and run script\n" : std::cout<<" [P] and run script\n";
  std::cout<<"PlayerP money: "<<map.get_PlayerP()->getMoney()<<"\n";
  std::cout<<"PlayerE money: "<<map.get_PlayerE()->getMoney()<<"\n\n";
  std::cout<<"Status Units belongs to Player P: \n";
  for(const auto& unit : map.get_PlayerP()->getUnits())
  {
    std::cout<<"+P+   Unit: "<<unit->getTypeInString()<<" ID: "<<unit->getId()<<" Postion: "<<unit->getObjectCoordinates()<< " Endurance: "<<unit->getEndurance()<<"\n";
  }
  
  std::cout<<"\nStatus Units belongs to Player E: \n";
  for(const auto& unit : map.get_PlayerE()->getUnits())
  {
    std::cout<<"+E+   Unit: "<<unit->getTypeInString()<<" ID: "<<unit->getId()<<" Postion: "<<unit->getObjectCoordinates()<< " Endurance: "<<unit->getEndurance()<<"\n";
  }
  std::cout<<"\n";
}