#include "../Include/map.hpp"
#include "../Include/Coordinates.hpp"
#include <iostream>
#include <algorithm>
#include <iostream>

Map::Map(const std::string& mapData):mapData_(mapData) {
            MAP_SIZE_X = getMapSizeX();
            MAP_SIZE_Y = getMapSizeY();
            matchCoordinatesWithFile();      
        };

size_t Map::getMapSizeX() const {
    auto it = std::find(mapData_.begin(),mapData_.end(),'\n');
        return std::distance(mapData_.begin(),it);
    }

    size_t Map::getMapSizeY() const {
        return std::count(mapData_.begin(), mapData_.end(), '\n');
    }

//Tutaj w tym przypiswywaniu bedize jeszcze jednostka na bank. Jakos to ogarniemy.
void Map::matchCoordinatesWithFile(){

    vectorOfObjects.resize(MAP_SIZE_X);

    for(size_t i = 0 ; i<MAP_SIZE_X;i++)
    {
        vectorOfObjects[i].resize(MAP_SIZE_Y);
        for(size_t j = 0 ; j<MAP_SIZE_Y ;j++)
        {   
            // //Coordinates c(i,j);
            // vectorOfObjects[i][j] = c;
        }
    }
}