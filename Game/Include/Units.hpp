#pragma once

#include <iostream>

#include "MapObjects.hpp"

class Knight : public Unit {
public:
  Knight(const Coordinates &coord);
  Knight(const Coordinates &cord, const unsigned short endurance);

private:
};

class Swordsman : public Unit {
public:
  Swordsman(const Coordinates &coord);
  Swordsman(const Coordinates &cord, const unsigned short endurance);

private:
};

class Archer : public Unit {
public:
  Archer(const Coordinates &coord);
  Archer(const Coordinates &cord, const unsigned short endurance);

private:
};

class Pikeman : public Unit {
public:
  Pikeman(const Coordinates &coord);
  Pikeman(const Coordinates &cord, const unsigned short endurance);

private:
};

class Catapult : public Unit {
public:
  Catapult(const Coordinates &coord);
  Catapult(const Coordinates &cord, const unsigned short endurance);

private:
};

class Ram : public Unit {
public:
  Ram(const Coordinates &coord);
  Ram(const Coordinates &cord, const unsigned short endurance);

private:
};

class Worker : public Unit {
public:
  Worker(const Coordinates &coord);
  Worker(const Coordinates &cord, const unsigned short endurance);

private:
};

class Base : public Unit {
public:
  Base(const Coordinates &cord);
  Base(const Coordinates &cord,const unsigned short endurance, const UnitTYPE& unitType, const unsigned short timeToProductionEnd);
  Base(const Coordinates &cord, const unsigned short endurance);

  inline bool Move([[maybe_unused]] const Coordinates &moveTo) override {std::cout << "Base Cannot move!\n";return false;}
  inline bool Attack([[maybe_unused]] std::shared_ptr<Unit> Solider) override {std::cout << "Base Cannot attack!\n"; return false;}

  bool Produce(const UnitTYPE &unitType) override;
  std::pair<UnitTYPE, unsigned short>& getProduction() {return production_;};
  UnitTYPE nextRound(){
    if(production_.second == 1 && production_.first != UnitTYPE::Base){
      std::cout<<"Production succesfull!\n";
        UnitTYPE ReadyToProduce = production_.first;
        production_.first = UnitTYPE::Base;
        production_.second = 0;
        return ReadyToProduce;
    }else if(production_.second != 0 && production_.first != UnitTYPE::Base)
    {
      production_.second--;
      std::cout<<"Produce will end in "<<production_.second<<" rounds\n";
      return UnitTYPE::Base;
    }

    std::cout<<"Base may produce units!\n";
    return UnitTYPE::Base;
}

private:
  unsigned short timeToProduce_{0};
  std::pair<UnitTYPE, unsigned short> production_ = std::make_pair(UnitTYPE::Base, timeToProduce_);
};