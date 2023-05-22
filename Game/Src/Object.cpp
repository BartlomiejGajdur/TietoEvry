#include "../Include/Object.hpp"
#include <iostream>
int MapObject::id_ = 0;

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

Unit::Unit(const UnitTYPE& unitType, unsigned short endurance, const Coordinates& ObjectCoordinates)
    :  MapObject(ObjectCoordinates),
      unitType_(unitType),
      endurance_(endurance){};


bool Unit::Move(const Coordinates& moveTo){
    size_t distance = Coordinates::distance(this->ObjectCoordinates_,moveTo);

    if(distance <= this->speedLeft_)
    {
        this->ObjectCoordinates_ = moveTo;
        this->speedLeft_-= distance;

        return true;
    }
    std::cerr<<"Dystans jest za duzy !\n";
    return false;
    
}

 bool Unit::Attack(std::shared_ptr<Unit> Solider){
    //Musi ona stać obok czyli distance z tej jednostki do solidera ma byc mniejszy lub rowny "zasiegAtaku"
    //Speed left czy tez po porstu speed ma byc conjamniej 1

    Solider->endurance_-= attackTable[static_cast<int>(unitType_)][static_cast<int>(Solider->unitType_)];
    std::cout<<"Udalo sie zaatakowac! Atak"<<static_cast<int>(unitType_)<<" na "<<static_cast<int>(Solider->unitType_)<<"   Odjeto: "<<attackTable[static_cast<int>(unitType_)][static_cast<int>(Solider->unitType_)]<<" \n";
    return true;
}