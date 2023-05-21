#include "../Include/map.hpp"
#include <iostream>


size_t Map::getMapSizeX() const {
    auto it = std::find(mapData_.begin(),mapData_.end(),'\n');
        return std::distance(mapData_.begin(),it);
    }

    size_t Map::getMapSizeY() const {
        return std::count(mapData_.begin(), mapData_.end(), '\n');
    }