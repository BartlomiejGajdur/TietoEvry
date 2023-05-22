#include "../Include/MapObjects.hpp"
#include "../Include/map.hpp"
#include <iostream>
int MapObject::counter = 0;

std::array<std::array<unsigned short, 8>, 7> attackTable{{
    {35, 35, 35, 35, 35, 50, 35, 35},
    {30, 30, 30, 20, 20, 30, 30, 30},
    {15, 15, 15, 15, 10, 10, 15, 15},
    {35, 15, 15, 15, 15, 10, 15, 10},
    {40, 40, 40, 40, 40, 40, 40, 50},
    {10, 10, 10, 10, 10, 10, 10, 50},
    {5, 5, 5, 5, 5, 5, 5, 1}
}};

MapObject::~MapObject(){}
Unit::~Unit(){}
Object::~Object(){}

Unit::Unit(const UnitTYPE& unitType, short endurance, const Coordinates& ObjectCoordinates)
    :  MapObject(ObjectCoordinates),
      unitType_(unitType),
      endurance_(endurance){};

Unit::Unit(const Coordinates& ObjectCoordinates, short endurance)
:  MapObject(ObjectCoordinates),
      endurance_(endurance){};


bool Unit::Move(const Coordinates& moveTo){
    short distance = Coordinates::distance(this->ObjectCoordinates_,moveTo);

    if(distance <= this->speed_)
    {
        this->ObjectCoordinates_ = moveTo;
        this->speed_-= distance;

        return true;
    }
    //Tutaj nie moze na zadna przeszkode isc czy na kopalnie 
    std::cerr<<"Too far!\n";
    return false;
    
}

 bool Unit::Attack(std::shared_ptr<Unit> Solider){

    if(attackDone_)
    {   
        std::cerr<<"You have already made an attack this turn!\n";
        return false;
    }
    if(Coordinates::distance(this->ObjectCoordinates_,Solider->ObjectCoordinates_)>this->attackRange_)
    {   
        std::cerr<<"The unit is too far away to attack!\n";
        return false;
    }
    if(this->speed_<1)
    {
       std::cerr<<"You need atleast one speed point to attack!\n";
       return false; 
    }

    //If everything is okey, perfrom attack acction

    Solider->endurance_-= attackTable[static_cast<int>(unitType_)][static_cast<int>(Solider->unitType_)];

    speed_--;
    attackDone_ = true;

    std::cout<<"Successfully attacked! Attack "<<static_cast<int>(unitType_)<<" on "<<static_cast<int>(Solider->unitType_)<<"!   Hit strength: "<<attackTable[static_cast<int>(unitType_)][static_cast<int>(Solider->unitType_)]<<" \n";
        
    return true; 
     
}