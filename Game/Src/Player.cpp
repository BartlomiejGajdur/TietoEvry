#include <algorithm>
#include <iostream>

#include "../Include/MapObjects.hpp"
#include "../Include/map.hpp"
#include "../Include/Player.hpp"
#include "../Include/Units.hpp"

void Player::printObjectsOwn() const
{
  for (auto v : unitsOwn_)
  {
    std::cout << "UnitType:" << v->getTypeInString()
              << " Unit ID:" << v->getId()
              << " Coordinates:" << v->getObjectCoordinates()
              << " Endurance:" << v->getEndurance() << "\n";
  }
}

std::shared_ptr<Unit> Player::getUnitByID(int iD)
{
  for (const auto &unit : this->getUnits())
  {
    if (unit->getId() == iD)
    {
      return unit;
    }
  }
  return nullptr;
}

bool Player::moveUnit(Map &map, int id, const Coordinates &coord)
{
  // Check if the given coordinates are within the map boundaries
  if (static_cast<size_t>(coord.getPositionX()) >= map.getMapSizeX() ||
      static_cast<size_t>(coord.getPositionY()) >= map.getMapSizeY())
  {
    std::cerr << "Cannot move out of map!\n";
    return false;
  }

  // Find the unit with the given ID in the player's owned units
  auto it = std::find_if(unitsOwn_.begin(), unitsOwn_.end(),
                         [=](std::shared_ptr<Unit> &objectsOwn)
                         {
                           return objectsOwn->getId() == id;
                         });
  if (it == unitsOwn_.end())
  {
    std::cerr << "Cannot find unit by given ID!\n";
    return false;
  }

  // Retrieve the found unit
  std::shared_ptr<Unit> &foundObject = *it;

  // Check if the unit can stand on the specified coordinates in the map
  if (!map.posibilityToStandOn(foundObject, coord))
  {
    std::cerr << "Cannot Stand on this field!\n";
    return false;
  }

  // Move the unit to the specified coordinates
  return foundObject->Move(coord);
}

std::shared_ptr<Unit> Player::getBase()
{
  // Find the player's base unit
  auto it = std::find_if(this->unitsOwn_.begin(), this->unitsOwn_.end(),
                         [](const std::shared_ptr<Unit> &unit)
                         {
                           return unit->getUnitType() == UnitTYPE::Base;
                         });

  // Return the found base unit if it exists
  if (it != this->unitsOwn_.end())
    return *it;

  // No base unit found, print an error message
  std::cout << "No base found!\n";
  return nullptr;
}


std::vector<Coordinates> Player::getWorkersCoordinates()
{
  std::vector<Coordinates> WorkersCoordinates{};

  std::for_each(this->getUnits().begin(), this->getUnits().end(), [&](const std::shared_ptr<Unit> unit)
                {
        std::shared_ptr<Worker> worker = std::dynamic_pointer_cast<Worker>(unit);
        if(worker)
            WorkersCoordinates.push_back(worker->getObjectCoordinates()); });

  return WorkersCoordinates;
}

void Player::addUnit(const UnitTYPE &unitType)
{
  switch (unitType)
  {
  case UnitTYPE::Knight:
    this->addUnit(std::make_shared<Knight>(this->getBase()->getObjectCoordinates()));
    break;
  case UnitTYPE::Swordsman:
    this->addUnit(std::make_shared<Swordsman>(this->getBase()->getObjectCoordinates()));
    break;
  case UnitTYPE::Archer:
    this->addUnit(std::make_shared<Archer>(this->getBase()->getObjectCoordinates()));
    break;
  case UnitTYPE::Pikeman:
    this->addUnit(std::make_shared<Pikeman>(this->getBase()->getObjectCoordinates()));
    break;
  case UnitTYPE::Ram:
    this->addUnit(std::make_shared<Ram>(this->getBase()->getObjectCoordinates()));
    break;
  case UnitTYPE::Catapult:
    this->addUnit(std::make_shared<Catapult>(this->getBase()->getObjectCoordinates()));
    break;
  case UnitTYPE::Worker:
    this->addUnit(std::make_shared<Worker>(this->getBase()->getObjectCoordinates()));
    break;
  default:
    break;
  }
}