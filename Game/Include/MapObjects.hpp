#pragma once

#include <string>
#include <memory>
#include <array>
#include "Coordinates.hpp"

enum class UnitTYPE {Knight = 0,Swordsman,Archer,Pikeman,Catapult,Ram,Worker,Base};
enum class ObjectTYPE { Road = 0, Mine = 6, Obstacle = 9};

class MapObject{
    public:
    MapObject(){};
    MapObject(const Coordinates& coordinates):ObjectCoordinates_(coordinates){};
    virtual ~MapObject() = 0;

    Coordinates getObjectCoordinates() const {return ObjectCoordinates_;};
    virtual int getId() const {return id_;};
    virtual std::string getTypeInString() const = 0;
    protected:
    Coordinates ObjectCoordinates_;
    static int counter;
    int id_ = counter;
};

class Unit : public MapObject{
    public:
        Unit(){};
        Unit(const UnitTYPE& unitType,short endurance, const Coordinates& ObjectCoordinates);
        Unit(const Coordinates& ObjectCoordinates, short endurance);
        virtual ~Unit() = 0;
        //Tutaj będą rózne sprawdzania w stylu czy sie moze przemiescic bo cos tam cos tam
        virtual bool Move(const Coordinates& moveTo);
        virtual bool Attack(std::shared_ptr<Unit> Solider);
        std::string getTypeInString() const override;
        short getSpeedLeft() const {return speed_;};
        
        UnitTYPE getUnitType()const {return unitType_;};
        short getEndurance() const {return endurance_;};
    protected:
        UnitTYPE unitType_;
        unsigned short  purchaseCost_,attackRange_,BuildTime_;   
        short endurance_, speed_;
        bool attackDone_ = false;
};

class Object : public MapObject{
    public:
        Object(){};
        Object(const ObjectTYPE& ObjectType):ObjectType_(ObjectType){};
        Object(const Coordinates& coordinates, const ObjectTYPE& ObjectType) : MapObject(coordinates),ObjectType_(ObjectType){};
        virtual ~Object() = 0;
       
       int getId() const override {return -1;};
       std::string getTypeInString() const override;
        
    protected:
        ObjectTYPE ObjectType_;  
};