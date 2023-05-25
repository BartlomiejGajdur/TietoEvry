#include "../Include/map.hpp"
#include "../Include/Coordinates.hpp"
#include "../Include/MapObjects.hpp"
#include "../Include/Object.hpp"
#include "../Include/Units.hpp"
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <functional>

std::string statusLocalization ="../Config/status.txt";

Map::Map(const std::string &mapData, std::shared_ptr<Player> PlayerP,
         std::shared_ptr<Player> PlayerE, size_t currentRound)
    : currentRound_(currentRound),mapData_(mapData), PlayerP_(PlayerP), PlayerE_(PlayerE) {
  MAP_SIZE_X = getMapSizeX();
  MAP_SIZE_Y = getMapSizeY();
  FileManager::ParseStatusFile(statusLocalization,*this);
  matchCoordinatesWithFile();
  
}

void Map::nextRound(){

  std::shared_ptr<Base> bazaP = std::dynamic_pointer_cast<Base>(PlayerP_->getBase());
  std::shared_ptr<Base> bazaE = std::dynamic_pointer_cast<Base>(PlayerE_->getBase());
  if(bazaP == nullptr)
  {
    std::cout<<"\n\n\nPLAYER_E WON!\n\n\n";
  }else if(bazaE == nullptr)
  {
    std::cout<<"\n\n\nPLAYER_P WON!\n\n\n";
  }else if(currentRound_>=MAX_GAME_ROUNDS)
  {
    int PlayerPUnitsCounter = PlayerP_->getUnits().size();
    int PlayerEUnitsCounter = PlayerE_->getUnits().size();

    if(PlayerPUnitsCounter == PlayerEUnitsCounter )
      std::cout<<"\n\n\n ITS A DRAW! \n\n\n";
    else 
      PlayerPUnitsCounter-PlayerEUnitsCounter>0?std::cout<<"\n\n\nPLAYER_P WON!\n\n\n":std::cout<<"\n\n\nPLAYER_E WON!\n\n\n";
  }
  else if(currentRound_ % 2 == 0){
    PlayerP_->addMoney(this->calculateIncomeFromWorkersInMine_PlayerP());
    UnitTYPE production = bazaP->nextRound();
    if(production != UnitTYPE::Base)
    {
      PlayerP_->addUnit(production);
    }
  }
  else{
    PlayerE_->addMoney(this->calculateIncomeFromWorkersInMine_PlayerP());
    UnitTYPE production = bazaE->nextRound();
    if(production != UnitTYPE::Base)
    {
      PlayerE_->addUnit(production);
    }
  }


  currentRound_++;
  FileManager::SaveStatusToFile(statusLocalization,*this);
}

size_t Map::getMapSizeX() {

  auto it = std::find(mapData_.begin(), mapData_.end(), '\n');
  return std::distance(mapData_.begin(), it);
}

size_t Map::getMapSizeY() {
  return std::count(mapData_.begin(), mapData_.end(), '\n');
}

std::shared_ptr<MapObject> Map::returnPointerFromGivenValue(char zn, int CoordX,
                                                            int CoordY) {
                                                            
  if (zn == '1') {
    if(auto deli = std::dynamic_pointer_cast<Base>(PlayerP_->getBase()))
    {
     
    }else{
      std::shared_ptr<Base> PlayerPBase = std::make_shared<Base>(Coordinates{CoordX, CoordY});
      PlayerP_->addUnit(PlayerPBase);
      return PlayerPBase;
    }
  return nullptr;
  } else if (zn == '2') {
    if(auto deli = std::dynamic_pointer_cast<Base>(PlayerE_->getBase()))
    {
      
    }else{
      std::shared_ptr<Base> PlayerEBase = std::make_shared<Base>(Coordinates{CoordX, CoordY});
      PlayerE_->addUnit(PlayerEBase);
      return PlayerEBase;
    }
  return nullptr;
  } else if (zn == '0') {
    return std::make_shared<Road>(Coordinates{CoordX, CoordY},
                                  ObjectTYPE::Road);
  } else if (zn == '6') {
    return std::make_shared<Mine>(Coordinates{CoordX, CoordY},
                                  ObjectTYPE::Mine);
  } else
    return std::make_shared<Obstacle>(Coordinates{CoordX, CoordY},
                                      ObjectTYPE::Obstacle);
}

void Map::matchCoordinatesWithFile() {
  std::string mapData = mapData_;
  int counter = 0;
  mapData.erase(std::remove(mapData.begin(), mapData.end(), '\n'),
                mapData.end());
  vectorOfObjects.resize(MAP_SIZE_Y);
  for (size_t i = 0; i < MAP_SIZE_Y; i++) {
    vectorOfObjects[i].resize(MAP_SIZE_X);
    for (size_t j = 0; j < MAP_SIZE_X; j++) {
      std::shared_ptr<MapObject> obj = returnPointerFromGivenValue(mapData[counter++], i, j);
      vectorOfObjects[i][j] = obj;
    }
  }
}

bool Map::posibilityToStandOn(std::shared_ptr<Unit> obj,
                              const Coordinates &coord) const {

  if (vectorOfObjects[coord.getPositionX()][coord.getPositionY()]
          ->getTypeInString() == "R") {
    return true;
  }

  if (obj->getUnitType() == UnitTYPE::Worker &&
      vectorOfObjects[coord.getPositionX()][coord.getPositionY()]
              ->getTypeInString() == "M") {
    return true;
  }
  return false;
}

bool Map::MoveAction_PlayerE(int id, const Coordinates &coord) {
  for (const auto &unit : PlayerP_->getUnits()) {
    if (unit->getObjectCoordinates() == coord) {
      std::cout << "Cannot stand on Unit that belongs to enemy[Looking for in "
                   "Player_P]!\n";
      return false;
    }
  }

  return PlayerE_->moveUnit(*this, id, coord);
}

bool Map::MoveAction_PlayerP(int id, const Coordinates &coord) {
  for (const auto &unit : PlayerE_->getUnits()) {
    if (unit->getObjectCoordinates() == coord) {
      std::cout << "Cannot stand on Unit that belongs to enemy[Looking for in "
                   "Player_E]!\n";
      return false;
    }
  }

  return PlayerP_->moveUnit(*this, id, coord);
}

bool Map::AttackAction_PlayerP(int PlayerUnitId, int EnemyPlayerUnitId) {

  std::shared_ptr<Unit> PlayerPUnit = PlayerP_->getUnitByID(PlayerUnitId);
  if (PlayerPUnit == nullptr) {
    std::cout << "Cannot find unit belongs to PlayerP that have given ID!\n";
    return false;
  }

  std::shared_ptr<Unit> PlayerEUnit = PlayerE_->getUnitByID(EnemyPlayerUnitId);
  if (PlayerE_->getUnitByID(EnemyPlayerUnitId) == nullptr) {
    std::cout << "Cannot find unit belongs to PlayerE that have given ID!\n";
    return false;
  }

  bool result = PlayerPUnit->Attack(PlayerEUnit);

  if (result && PlayerEUnit->getEndurance() <= 0) {
    std::cout << "The attacked unit's health drops below 0. The unit dies !\n";
    PlayerE_->getUnits().erase(
        std::remove_if(PlayerE_->getUnits().begin(), PlayerE_->getUnits().end(),
                       [&](std::shared_ptr<Unit> unit) {
                         return unit->getId() == EnemyPlayerUnitId;
                       }),
        PlayerE_->getUnits().end());
  }

  return result;
}

bool Map::AttackAction_PlayerE(int PlayerUnitId, int EnemyPlayerUnitId) {

  std::shared_ptr<Unit> PlayerEUnit = PlayerE_->getUnitByID(PlayerUnitId);
  if (PlayerEUnit == nullptr) {
    std::cout << "Cannot find unit belongs to PlayerE that have given ID!\n";
    return false;
  }

  std::shared_ptr<Unit> PlayerPUnit = PlayerP_->getUnitByID(EnemyPlayerUnitId);
  if (PlayerP_->getUnitByID(EnemyPlayerUnitId) == nullptr) {
    std::cout << "Cannot find unit belongs to PlayerP that have given ID!\n";
    return false;
  }
  bool result = PlayerEUnit->Attack(PlayerPUnit);

  if (result && PlayerPUnit->getEndurance() <= 0) {
    std::cout << "The attacked unit's health drops below 0. The unit dies !\n";
    PlayerP_->getUnits().erase(
        std::remove_if(PlayerP_->getUnits().begin(), PlayerP_->getUnits().end(),
                       [&](std::shared_ptr<Unit> unit) {
                         return unit->getId() == EnemyPlayerUnitId;
                       }),
        PlayerP_->getUnits().end());
  }

  return result;
}

bool Map::ProductAction_PlayerP(const UnitTYPE &unitType) {
  if (PlayerP_->getMoney() < Unit::getPurchaseCost(unitType)) {
    std::cout << "Lack of money to produce unit!\n";
    return false;
  }
  if (!PlayerP_->getBase()->Produce(unitType))
    return false;

  PlayerP_->substractMoney(Unit::getPurchaseCost(unitType));
  return true;
}

bool Map::ProductAction_PlayerE(const UnitTYPE &unitType) {

  if (PlayerE_->getMoney() < Unit::getPurchaseCost(unitType)) {
    std::cout << "Lack of money to produce unit!\n";
    return false;
  }

  if (!PlayerE_->getBase()->Produce(unitType))
    return false;

  PlayerE_->substractMoney(Unit::getPurchaseCost(unitType));
  return true;
}

std::vector<Coordinates> Map::getMineCoordinates(){
    std::vector<Coordinates> MineCoordinates{};

    std::for_each(this->vectorOfObjects.begin(),this->vectorOfObjects.end(),[&](const std::vector<std::shared_ptr<MapObject>> vectorObjects)
    {
       std::for_each(vectorObjects.begin(),vectorObjects.end(),[&](const std::shared_ptr<MapObject> object)
          {
              std::shared_ptr<Mine> mine = std::dynamic_pointer_cast<Mine>(object);
              if(mine)
                  MineCoordinates.push_back(mine->getObjectCoordinates());
          });
    });

    return MineCoordinates;
}

struct CoordinatesHash {
  size_t operator()(const Coordinates& coord) const {
    std::hash<size_t> hasher;
    size_t hash = 0;
    hash ^= hasher(coord.getPositionX()) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    hash ^= hasher(coord.getPositionY()) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    return hash;
  }
};

size_t Map::countWorkersInMine(const std::vector<Coordinates>& mineCoordinates, const std::vector<Coordinates>& workersCoordinates) {
  std::unordered_map<Coordinates, size_t, CoordinatesHash> workersCount;
  size_t counter = 0;

  for (const auto& Coord : mineCoordinates) {
    workersCount[Coord] = 0;
  }

  for (const auto& Coord : workersCoordinates) {
    if (workersCount.find(Coord) != workersCount.end()) {
      counter++;
    }
  }

  return counter;
}

  size_t Map::calculateIncomeFromWorkersInMine_PlayerP(){
    return this->countWorkersInMine(this->getMineCoordinates(),this->PlayerP_->getWorkersCoordinates()) * INCOME_PER_WORKER;
  }

  size_t Map::calculateIncomeFromWorkersInMine_PlayerE(){
    return this->countWorkersInMine(this->getMineCoordinates(),this->PlayerE_->getWorkersCoordinates()) * INCOME_PER_WORKER;
  }
