#include <iostream>

#include "../Include/MapObjects.hpp"
#include "../Include/map.hpp"
#include "../Include/Units.hpp"

int MapObject::counter = 0;

std::array<std::array<unsigned short, 8>, 7> attackTable{
    {{35, 35, 35, 35, 35, 50, 35, 35},
     {30, 30, 30, 20, 20, 30, 30, 30},
     {15, 15, 15, 15, 10, 10, 15, 15},
     {35, 15, 15, 15, 15, 10, 15, 10},
     {40, 40, 40, 40, 40, 40, 40, 50},
     {10, 10, 10, 10, 10, 10, 10, 50},
     {5, 5, 5, 5, 5, 5, 5, 1}}};

MapObject::~MapObject() {}
Unit::~Unit() {}
Object::~Object() {}

Unit::Unit(const UnitTYPE &unitType, short endurance,
           const Coordinates &ObjectCoordinates)
    : MapObject(ObjectCoordinates), unitType_(unitType),
      endurance_(endurance){};

Unit::Unit(const Coordinates &ObjectCoordinates, short endurance)
    : MapObject(ObjectCoordinates), endurance_(endurance){};

bool Unit::Produce([[maybe_unused]] const UnitTYPE &unitType)
{
  std::cout << "Incorrect action " << this->getTypeInString()
            << " cannot produce Units!\n";
  return false;
}

bool Unit::Move(const Coordinates &moveTo)
{
  short distance = Coordinates::distance(this->ObjectCoordinates_, moveTo);

  if (distance <= this->speed_)
  {
    this->ObjectCoordinates_ = moveTo;
    this->speed_ -= distance;

    return true;
  }
  std::cout << "Too far!\n";
  return false;
}

bool Unit::Attack(std::shared_ptr<Unit> Solider)
{

  if (attackDone_)
  {
    std::cerr << "You have already made an attack this turn!\n";
    return false;
  }
  if (Coordinates::distance(this->ObjectCoordinates_,
                            Solider->ObjectCoordinates_) > this->attackRange_)
  {
    std::cerr << "The unit is too far away to attack!\n";
    return false;
  }
  if (this->speed_ < 1)
  {
    std::cerr << "You need atleast one speed point to attack!\n";
    return false;
  }

  // If everything is okey, perfrom attack acction

  Solider->endurance_ -= attackTable[static_cast<int>(unitType_)]
                                    [static_cast<int>(Solider->unitType_)];

  speed_--;
  attackDone_ = true;

  std::cout << "Successfully attacked! Attack " << static_cast<int>(unitType_)
            << " on " << static_cast<int>(Solider->unitType_)
            << "!   Hit strength: "
            << attackTable[static_cast<int>(unitType_)]
                          [static_cast<int>(Solider->unitType_)]
            << " \n";

  return true;
}

std::string Unit::getTypeInString() const
{
  switch (unitType_)
  {
  case UnitTYPE::Knight:
    return "K";
    break;
  case UnitTYPE::Swordsman:
    return "S";
    break;
  case UnitTYPE::Archer:
    return "A";
    break;
  case UnitTYPE::Pikeman:
    return "P";
    break;
  case UnitTYPE::Catapult:
    return "C";
    break;
  case UnitTYPE::Ram:
    return "R";
    break;
  case UnitTYPE::Worker:
    return "W";
    break;
  case UnitTYPE::Base:
    return "B";
    break;
  default:
    return "New";
    break;
  }
}

std::string Object::getTypeInString() const
{
  switch (ObjectType_)
  {
  case ObjectTYPE::Road:
    return "R";
    break;
  case ObjectTYPE::Mine:
    return "M";
    break;
  case ObjectTYPE::Obstacle:
    return "O";
  case ObjectTYPE::BaseP:
    return "1";
  case ObjectTYPE::BaseE:
    return "2";
    break;
  default:
    return "New";
    break;
  }
}

unsigned short Unit::getPurchaseCost(const UnitTYPE &unitType)
{
  switch (unitType)
  {
  case UnitTYPE::Knight:
    return 400;
    break;
  case UnitTYPE::Swordsman:
    return 250;
    break;
  case UnitTYPE::Archer:
    return 250;
    break;
  case UnitTYPE::Pikeman:
    return 200;
    break;
  case UnitTYPE::Ram:
    return 500;
    break;
  case UnitTYPE::Catapult:
    return 800;
    break;
  case UnitTYPE::Worker:
    return 100;
    break;
  case UnitTYPE::Base:
    return 0;
    break;
  default:
    return 0;
    break;
  }
}

unsigned short Unit::getBuildTime(const UnitTYPE &unitType)
{
  switch (unitType)
  {
  case UnitTYPE::Knight:
    return 5;
    break;
  case UnitTYPE::Swordsman:
    return 3;
    break;
  case UnitTYPE::Archer:
    return 3;
    break;
  case UnitTYPE::Pikeman:
    return 3;
    break;
  case UnitTYPE::Ram:
    return 4;
    break;
  case UnitTYPE::Catapult:
    return 6;
    break;
  case UnitTYPE::Worker:
    return 2;
    break;
  case UnitTYPE::Base:
    return 0;
    break;
  default:
    return 0;
    break;
  }
}

std::string Unit::getUnitTypeInString(const UnitTYPE unitType)
{
  switch (unitType)
  {
  case UnitTYPE::Knight:
    return "K";
    break;
  case UnitTYPE::Swordsman:
    return "S";
    break;
  case UnitTYPE::Archer:
    return "A";
    break;
  case UnitTYPE::Pikeman:
    return "P";
    break;
  case UnitTYPE::Catapult:
    return "C";
    break;
  case UnitTYPE::Ram:
    return "R";
    break;
  case UnitTYPE::Worker:
    return "W";
    break;
  case UnitTYPE::Base:
    return "B";
    break;
  default:
    return "New";
    break;
  }
}

UnitTYPE Unit::getUnitTypeFromString(const std::string &unitString)
{
  char unitCode = unitString[0];

  switch (unitCode)
  {
  case 'K':
    return UnitTYPE::Knight;
    break;
  case 'S':
    return UnitTYPE::Swordsman;
    break;
  case 'A':
    return UnitTYPE::Archer;
    break;
  case 'P':
    return UnitTYPE::Pikeman;
    break;
  case 'C':
    return UnitTYPE::Catapult;
    break;
  case 'R':
    return UnitTYPE::Ram;
    break;
  case 'W':
    return UnitTYPE::Worker;
    break;
  default:
    return UnitTYPE::Base;
    break;
  }
}

std::shared_ptr<Unit> Unit::returnUnit(const std::string &unitType, const int &id, const int &PosX, const int &PosY, const short &endurance, const std::string &productionType, const int &productionAmount)
{
  int unitTypeCode = static_cast<int>(unitType[0]);
  switch (unitTypeCode)
  {
  case 'K':
    return std::make_shared<Knight>(id, Coordinates(PosX, PosY), endurance);
    break;

  case 'S':
    return std::make_shared<Swordsman>(id, Coordinates(PosX, PosY), endurance);
    break;

  case 'A':
    return std::make_shared<Archer>(id, Coordinates(PosX, PosY), endurance);
    break;

  case 'P':
    return std::make_shared<Pikeman>(id, Coordinates(PosX, PosY), endurance);
    break;

  case 'C':
    return std::make_shared<Catapult>(id, Coordinates(PosX, PosY), endurance);
    break;

  case 'R':
    return std::make_shared<Ram>(id, Coordinates(PosX, PosY), endurance);
    break;

  case 'W':
    return std::make_shared<Worker>(id, Coordinates(PosX, PosY), endurance);
    break;

  case 'B':
    return std::make_shared<Base>(id, Coordinates(PosX, PosY), endurance, Unit::getUnitTypeFromString(productionType), productionAmount);
    break;
  default:
    return nullptr;
    break;
  }
}
