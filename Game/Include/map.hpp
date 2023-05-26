#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "Coordinates.hpp"
#include "FileManager.hpp"
#include "MapObjects.hpp"
#include "Player.hpp"
#include "Time.hpp"

const size_t INCOME_PER_WORKER = 50;

class Player;

class Map : public Observer {
public:
  Map(const std::string &mapData, const std::shared_ptr<Player> PlayerP,
      const std::shared_ptr<Player> PlayerE, size_t currentRound);

  size_t getMapSizeX(); // Get the size of the map in the X dimension
  size_t getMapSizeY(); // Get the size of the map in the Y dimension
  bool posibilityToStandOn(std::shared_ptr<Unit> obj,
                           const Coordinates &coord) const; // Check if it's possible to stand on a specific coordinate

  std::shared_ptr<Player> get_PlayerE() { return PlayerE_; }; // Get the PlayerE object
  std::shared_ptr<Player> get_PlayerP() { return PlayerP_; }; // Get the PlayerP object

  bool MoveAction_PlayerP(int id, const Coordinates &coord); // Perform a move action for PlayerP's unit with the given ID
  bool MoveAction_PlayerE(int id, const Coordinates &coord); // Perform a move action for PlayerE's unit with the given ID

  bool AttackAction_PlayerP(int PlayerUnitId, int EnemyPlayerUnitId); // Perform an attack action for PlayerP's units
  bool AttackAction_PlayerE(int PlayerUnitId, int EnemyPlayerUnitId); // Perform an attack action for PlayerE's units

  bool ProductAction_PlayerP(const UnitTYPE &unitType); // Perform a production action for PlayerP
  bool ProductAction_PlayerE(const UnitTYPE &unitType); // Perform a production action for PlayerE

  size_t countWorkersInMine(const std::vector<Coordinates>& mineCoordinates, const std::vector<Coordinates>& workersCoordinates); // Count the number of workers in the mine area
  std::vector<Coordinates> getMineCoordinates(); // Get the coordinates of the mine areas
  size_t calculateIncomeFromWorkersInMine_PlayerP(); // Calculate the income from workers in the mine for PlayerP
  size_t calculateIncomeFromWorkersInMine_PlayerE(); // Calculate the income from workers in the mine for PlayerE

  void nextRound() override; // Proceed to the next round
  void setRound(size_t round) {currentRound_ = round;}; // Set the current round number
  size_t getRound() const {return currentRound_;}; // Get the current round number
private:
  size_t currentRound_{0};
  std::string mapData_;
  size_t MAP_SIZE_X, MAP_SIZE_Y;
  std::shared_ptr<Player> PlayerP_;
  std::shared_ptr<Player> PlayerE_;

  std::vector<std::vector<std::shared_ptr<MapObject>>> vectorOfObjects;

  std::shared_ptr<MapObject> returnPointerFromGivenValue(char zn, int CoordX,
                                                         int CoordY); // Return a pointer to the map object based on the given value and coordinates
  void matchCoordinatesWithFile(); // Match the coordinates with the map file
};
