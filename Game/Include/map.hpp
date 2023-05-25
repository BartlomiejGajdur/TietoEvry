#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "Coordinates.hpp"
#include "FileManager.hpp"
#include "MapObjects.hpp"
#include "Player.hpp"

const size_t INCOME_PER_WORKER = 50;

class Player;

class Map {
public:
  Map(const std::string &mapData, const std::shared_ptr<Player> PlayerP,
      const std::shared_ptr<Player> PlayerE);

  size_t getMapSizeX();
  size_t getMapSizeY();
  bool posibilityToStandOn(std::shared_ptr<Unit> obj,
                           const Coordinates &coord) const;

  std::shared_ptr<Player> get_PlayerE() { return PlayerE_; };
  std::shared_ptr<Player> get_PlayerP() { return PlayerP_; };

  bool MoveAction_PlayerP(int id, const Coordinates &coord);
  bool MoveAction_PlayerE(int id, const Coordinates &coord);

  bool AttackAction_PlayerP(int PlayerUnitId, int EnemyPlayerUnitId);
  bool AttackAction_PlayerE(int PlayerUnitId, int EnemyPlayerUnitId);

  bool ProductAction_PlayerP(const UnitTYPE &unitType);
  bool ProductAction_PlayerE(const UnitTYPE &unitType);

  size_t countWorkersInMine(const std::vector<Coordinates>& mineCoordinates, const std::vector<Coordinates>& workersCoordinates);
  std::vector<Coordinates> getMineCoordinates();
  size_t calculateIncomeFromWorkersInMine_PlayerP();
  size_t calculateIncomeFromWorkersInMine_PlayerE();

private:
  std::string mapData_;
  size_t MAP_SIZE_X, MAP_SIZE_Y;
  std::shared_ptr<Player> PlayerP_;
  std::shared_ptr<Player> PlayerE_;

  std::vector<std::vector<std::shared_ptr<MapObject>>> vectorOfObjects;

  std::shared_ptr<MapObject> returnPointerFromGivenValue(char zn, int CoordX,
                                                         int CoordY);
  void matchCoordinatesWithFile();
  
};
