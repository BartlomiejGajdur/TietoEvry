#pragma once
#include "Player.hpp"

#include <string>
#include <algorithm>
#include <vector>
#include "Coordinates.hpp"
#include "FileManager.hpp"
#include "MapObjects.hpp"
#include <iostream>
class Player;

class Map {
public:
    Map(const std::string& mapData,const std::shared_ptr<Player> PlayerP,const std::shared_ptr<Player> PlayerE);

    size_t getMapSizeX();
    size_t getMapSizeY();
    bool posibilityToStandOn(std::shared_ptr<Unit> obj, const Coordinates& coord) const;

    std::shared_ptr<Player>& getPlayerBelongsToEnemy()  {return PlayerE_;};
    std::shared_ptr<Player>& getPlayerBelongsToUs()  {return PlayerP_;};

    //Podajemy Id jednostki a nastapnie czy staniemy na jendostce przeciwnika, a potem wykonuje te funkcje ktora sobie juz reszte sprawdzi.
    bool performMoveByPlayerBelongsToUs(int id,const Coordinates& coord);
    bool performMoveByPlayerBelongsToEnemy(int id,const Coordinates& coord);

    bool performAttackByPlayerBelongsToUs(int PlayerUnitId, int EnemyPlayerUnitId);
    bool performAttackByPlayerBelongsToEnemy(int PlayerUnitId, int EnemyPlayerUnitId);

    bool performBuildByPlayerBelongsToUs(const UnitTYPE& unitType);
    bool performBuildByPlayerBelongsToEnemy(const UnitTYPE& unitType);

private:
    std::string mapData_;
    size_t MAP_SIZE_X, MAP_SIZE_Y;
    std::shared_ptr<Player> PlayerP_;
    std::shared_ptr<Player> PlayerE_;

    std::vector<std::vector<std::shared_ptr<MapObject>>> vectorOfObjects;

    std::shared_ptr<MapObject> returnPointerFromGivenValue(char zn, int CoordX, int CoordY);
    void matchCoordinatesWithFile();
};
