#pragma once
#include "MapObjects.hpp"
#include "Coordinates.hpp"
#include "map.hpp"
#include <vector>
#include <memory>
class Map;

class Player{
    public:
        Player(){};

        long getMoney() const {return money_;};
        void addMoney(long money) { money_ += money;};
        void addUnit(const std::shared_ptr<Unit>& Unit) { unitsOwn_.push_back(Unit);};
        void printObjectsOwn()const;
        std::vector<std::shared_ptr<Unit>> getUnits() const {return unitsOwn_;};

        bool moveUnit(Map& map, int id,const Coordinates& coord);
        // bool attackUnit(Map& map, int UnitOwn_ID, int UnitToAttackID)
        // {
        //     return false;
        // }
    private:

        long money_{2000};
        std::vector<std::shared_ptr<Unit>> unitsOwn_;

};