#pragma once

#include <memory>
#include <vector>

#include "Coordinates.hpp"
#include "MapObjects.hpp"
#include "map.hpp"

class Map;

class Player {
public:
  Player(){};

  long getMoney() const { return money_; };
  void addMoney(long money) { money_ += money; };
  void substractMoney(long money) { money_ -= money; };

  std::vector<std::shared_ptr<Unit>> &getUnits() { return unitsOwn_; };
  std::shared_ptr<Unit> getUnitByID(int iD);
  std::shared_ptr<Unit> getBase();
  bool moveUnit(Map &map, int id, const Coordinates &coord);

  inline void addUnit(const std::shared_ptr<Unit> &Unit) {unitsOwn_.push_back(Unit);};
  void printObjectsOwn() const;
  
private:
  long money_{2000};
  std::vector<std::shared_ptr<Unit>> unitsOwn_;
};