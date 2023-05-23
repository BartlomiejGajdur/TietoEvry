#pragma once
#include "Player.hpp"

#include <string>
#include <algorithm>
#include <vector>
#include "Coordinates.hpp"
#include "FileManager.hpp"
#include "MapObjects.hpp"
class Player;

class Map {
public:
    Map(const std::string& mapData,const std::unique_ptr<Player> PlayerP,const std::unique_ptr<Player> PlayerE);

    size_t getMapSizeX();
    size_t getMapSizeY();
    bool posibilityToStandOn(std::shared_ptr<Unit> obj, const Coordinates& coord) const;

private:
    std::string mapData_;
    size_t MAP_SIZE_X, MAP_SIZE_Y;
    std::unique_ptr<Player> PlayerP_;
    std::unique_ptr<Player> PlayerE_;

    std::vector<std::vector<std::shared_ptr<MapObject>>> vectorOfObjects;

    std::shared_ptr<MapObject> returnPointerFromGivenValue(char zn, int CoordX, int CoordY);
    void matchCoordinatesWithFile();
};
