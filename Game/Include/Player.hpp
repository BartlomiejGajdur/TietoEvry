#pragma once
#include "MapObjects.hpp"
#include "Coordinates.hpp"
#include "map.hpp"
#include <vector>
#include <memory>

// Forward declaration klasy Map
class Map;

class Player {
public:
    Player(){};

    long getMoney() const { return money_; }
    void addMoney(long money) { money_ = money; }
    void addObject(std::shared_ptr<Unit>& object) { unitsOwn_.push_back(object); }
    void printObjectsOwn() const;

    bool moveUnit(Map& map, int id, const Coordinates& coord);

private:
    long money_{2000};
    std::vector<std::shared_ptr<Unit>> unitsOwn_;
};