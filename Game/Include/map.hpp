#pragma once

#include <string>
#include <algorithm>
#include <vector>
#include "../Include/Coordinates.hpp"
#include "../Include/FileManager.hpp"
#include "../Include/Object.hpp"


class Map{
    public:
        Map(const std::string& mapData);

        size_t getMapSizeX() const;
        size_t getMapSizeY() const;
        //Find and return obj with given id 

        size_t MAP_SIZE_X, MAP_SIZE_Y;
    private:
        std::string mapData_;
        //Tutaj będą raczje mapObjects
        std::vector<std::vector<std::shared_ptr<MapObject>>> vectorOfObjects;

        void matchCoordinatesWithFile();
};