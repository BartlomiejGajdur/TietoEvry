#pragma once

#include <string>
#include <memory>
#include <array>
#include "Coordinates.hpp"

enum class UnitTYPE {Knight = 0,Swordsman,Archer,Pikeman,Ram,Catapult,Worker,Base};
enum class ObjectTYPE {Mine, Obstacle, Road};
//GetID w objectType bedzie zwracac -1 np hehe

class MapObject{
    public:
    MapObject(){};
    MapObject(const Coordinates& coordinates):ObjectCoordinates_(coordinates){};
    virtual ~MapObject() = 0;

    Coordinates getObjectCoordinates() const {return ObjectCoordinates_;};

    protected:
    Coordinates ObjectCoordinates_;
};



class Unit : public MapObject{
    public:
        Unit(){};
        Unit(const UnitTYPE& unitType,unsigned short endurance, const Coordinates& ObjectCoordinates);
        virtual ~Unit() = 0;
        //Tutaj będą rózne sprawdzania w stylu czy sie moze przemiescic bo cos tam cos tam
        virtual bool Move(const Coordinates& moveTo);
        virtual bool Attack(std::shared_ptr<Unit> Solider);

        unsigned short getSpeedLeft() const {return speedLeft_;};
        unsigned short getId() const {return id_;};
        UnitTYPE getUnitType()const {return unitType_;};
        unsigned short getEndurance() const {return endurance_;};
    protected:
        UnitTYPE unitType_;
        unsigned short endurance_, speed_, purchaseCost_,attackRange_,BuildTime_;
        unsigned short speedLeft_ = speed_;
        static unsigned short id_;
};