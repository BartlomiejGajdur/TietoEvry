#pragma once

#include <string>
#include <algorithm>
#include <vector>
#include "../Include/Coordinates.hpp"
#include "../Include/FileManager.hpp"


class Map{
    public:
        Map(const std::string& mapData);

        size_t getMapSizeX() const;
        size_t getMapSizeY() const;

        size_t MAP_SIZE_X, MAP_SIZE_Y;
    private:
        std::string mapData_;
        std::vector<std::vector<Coordinates>> vectorOfCoordinates;

        void matchCoordinatesWithFile();
};