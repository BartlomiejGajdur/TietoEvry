#pragma once

#include <string>
#include <algorithm>
#include <vector>
#include "../Include/Coordinates.hpp"
#include "../Include/FileManager.hpp"
#include "../Include/MapObjects.hpp"
#include "../Include/Player.hpp"


class Map{
    public:
        Map(const std::string& mapData);

        size_t getMapSizeX();
        size_t getMapSizeY();
        //Find and return obj with given id 
        bool posibilityToStandOn(std::shared_ptr<Unit> obj, const Coordinates& coord) const;
        
    private:
    
        std::string mapData_;
        size_t MAP_SIZE_X, MAP_SIZE_Y; 
        // Player PlayerP{2000};
        // Player PlayerE{2000};

        std::vector<std::vector<std::shared_ptr<MapObject>>> vectorOfObjects;

        std::shared_ptr<MapObject> returnPointerFromGivenValue(char zn,int CoordX, int CoordY);
        void matchCoordinatesWithFile();
};