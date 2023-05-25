#include <algorithm>
#include <iostream>

#include "../Include/Player.hpp"
#include "../Include/MapObjects.hpp"
#include "../Include/map.hpp"


void Player::printObjectsOwn() const {
  for (auto v : unitsOwn_) {
    std::cout << "UnitType:" << v->getTypeInString()
              << " Unit ID:" << v->getId()
              << " Coordinates:" << v->getObjectCoordinates()
              << " Endurance:" << v->getEndurance() << "\n";
  }
}

std::shared_ptr<Unit> Player::getUnitByID(int iD) {
  for (const auto &unit : this->getUnits()) {
    if (unit->getId() == iD) {
      return unit;
    }
  }
  return nullptr;
}

bool Player::moveUnit(Map &map, int id, const Coordinates &coord) {

  if (static_cast<size_t>(coord.getPositionX()) >= map.getMapSizeX() ||
      static_cast<size_t>(coord.getPositionY()) >= map.getMapSizeY()) {
    std::cerr << "Cannot move out of map!\n";
    return false;
  }

  auto it = std::find_if(unitsOwn_.begin(), unitsOwn_.end(),
                         [=](std::shared_ptr<Unit> &objectsOwn) {
                           return objectsOwn->getId() == id;
                         });
  if (it == unitsOwn_.end()) {
    std::cerr << "Cannot find unit by given ID!\n";
    return false;
  }

  std::shared_ptr<Unit> &foundObject = *it;
  if (!map.posibilityToStandOn(foundObject, coord)) {
    std::cerr << "Cannot Stand on this field!\n";
    return false;
  }

  return foundObject->Move(coord);
}

std::shared_ptr<Unit> Player::getBase() {
  auto it = std::find_if(this->unitsOwn_.begin(), this->unitsOwn_.end(),
                         [](const std::shared_ptr<Unit> &unit) {
                           return unit->getUnitType() == UnitTYPE::Base;
                         });

  if (it != this->unitsOwn_.end())
    return *it;

  std::cout << "No base found!\n";
  return nullptr;
}