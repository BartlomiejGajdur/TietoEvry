#include "../Include/Player.hpp"
#include <algorithm>
#include <iostream>

void Player::printObjectsOwn() const{
    for(const auto& v: unitsOwn_)
    {
        std::cout<<v<<"\n";
    }
}

// bool Player::moveUnit(const Map& map, int id,const Coordinates& coord){
//     // auto it = std::find_if(unitsOwn_.begin(),unitsOwn_.end(),[&](const MapObject& objectsOwn){ return objectsOwn.getId() == id;});
//     // if(it == unitsOwn_.end())
//     // {   
//     //     std::cout<<"Cannot find unit by given ID!\n";
//     //     return false;
//     // }
//     // if(!map.posibilityToStandOn(it[0],coord))
//     // {
//     //     std::cout<<"Cannot Stand on this field!\n";
//     //     return false;
//     // }
//     //Czy nie wyjdzie za mape 
//     map.getMapSizeX();
//     id =10;
//     if(coord == Coordinates{1,2})


// return true;
        
// }