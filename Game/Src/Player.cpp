#include "../Include/Player.hpp"
#include "../Include/map.hpp"
#include <algorithm>
#include <iostream>

void Player::printObjectsOwn() const{
    for( auto v: unitsOwn_)
    {
        std::cout<<"UnitType:" <<v->getTypeInString()<<" Unit ID:"<<v->getId()<<" Coordinates:"<<v->getObjectCoordinates()<<" Endurance:"<<v->getEndurance()<<"\n";
    }
}

bool Player::moveUnit(Map& map, int id,const Coordinates& coord){
    auto it = std::find_if(unitsOwn_.begin(),unitsOwn_.end(),[=](std::shared_ptr<Unit>& objectsOwn){ return objectsOwn->getId() == id;});
    if(it == unitsOwn_.end())
    {   
        std::cout<<"Cannot find unit by given ID!\n";
        return false;
    }
    if(!map.posibilityToStandOn(it[0],coord))
    {
        std::cout<<"Cannot Stand on this field!\n";
        return false;
    }

return true;
        
}