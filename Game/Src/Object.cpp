#include "../Include/Object.hpp"

unsigned short Unit::id_ = 0;

MapObject::~MapObject(){}

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
    return false;
    
}