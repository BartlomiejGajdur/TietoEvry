#include "../Include/map.hpp"
#include "../Include/Coordinates.hpp"
#include "../Include/MapObjects.hpp"
#include "../Include/Units.hpp"
#include "../Include/Object.hpp"
#include <iostream>
#include <algorithm>
#include <iostream>

Map::Map(const std::string& mapData, std::unique_ptr<Player> PlayerP, std::unique_ptr<Player> PlayerE)
    : mapData_(mapData), PlayerP_(std::move(PlayerP)), PlayerE_(std::move(PlayerE))
{
    MAP_SIZE_X = getMapSizeX();
    MAP_SIZE_Y = getMapSizeY();
    matchCoordinatesWithFile();
}

size_t Map::getMapSizeX() {

    auto it = std::find(mapData_.begin(),mapData_.end(),'\n');
        return std::distance(mapData_.begin(),it);
    }

    size_t Map::getMapSizeY() {
        return std::count(mapData_.begin(), mapData_.end(), '\n');
    }

std::shared_ptr<MapObject> Map::returnPointerFromGivenValue(char zn,int CoordX, int CoordY){
    if(zn == '1' || zn == '2')
    {   
        //Pushback do playera 1
        return std::make_shared<Base>(Coordinates{CoordX,CoordY});
    }else if(zn == '0')
    {
        return std::make_shared<Road>(Coordinates{CoordX,CoordY},ObjectTYPE::Road);
    }else if(zn == '6')
    {
        return std::make_shared<Mine>(Coordinates{CoordX,CoordY},ObjectTYPE::Mine);
    }else
        return std::make_shared<Obstacle>(Coordinates{CoordX,CoordY},ObjectTYPE::Obstacle);
}
    

//Tutaj w tym przypiswywaniu bedize jeszcze jednostka na bank. Jakos to ogarniemy.
void Map::matchCoordinatesWithFile(){
    std::string mapData = mapData_;
    int counter = 0;
    mapData.erase(std::remove(mapData.begin(),mapData.end(),'\n'),mapData.end());
    vectorOfObjects.resize(MAP_SIZE_Y);
    for(size_t i = 0 ; i<MAP_SIZE_Y;i++)
    {
        vectorOfObjects[i].resize(MAP_SIZE_X);
        for(size_t j = 0 ; j<MAP_SIZE_X ;j++)
        {   
            //std::cout<<"vector["<<i<<"]["<<j<<"]"<<" -> "<<mapData[counter]<<"\n";
            std::shared_ptr<MapObject>  obj= returnPointerFromGivenValue(mapData[counter++],i,j);;
            vectorOfObjects[i][j] = obj;
        }
    }
}

bool Map::posibilityToStandOn(std::shared_ptr<Unit> obj,const Coordinates& coord)const {
    
    if(vectorOfObjects[coord.getPositionX()][coord.getPositionY()]->print()=="Road | ")
    {
        return true;
    }

    if(obj->getUnitType() == UnitTYPE::Worker && vectorOfObjects[coord.getPositionX()][coord.getPositionY()]->print()=="Mine | " )
    {
        return true;
    }

    return false;
}