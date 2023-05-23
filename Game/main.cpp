#include <iostream>
#include "Include/FileManager.hpp"
#include <algorithm>
#include "Include/Coordinates.hpp"
#include "Include/MapObjects.hpp"
#include "Include/map.hpp"
#include "Include/Units.hpp"
#include "Include/Player.hpp"
#include <memory>

std::string configLocalization ="../Config/mapa.txt";


int main(){

    FileManager mapa("../Config/mapa.txt");
    mapa.openFile();
    mapa.readFromFile();
    std::string line = mapa.getFileContent();

    Map maps(line,std::make_shared <Player>(),std::make_shared  <Player>());

    maps.getPlayerBelongsToEnemy()->addUnit(std::make_shared<Knight>());
    maps.getPlayerBelongsToEnemy()->addUnit(std::make_shared<Swordsman>());

    maps.getPlayerBelongsToUs()->addUnit(std::make_shared<Swordsman>());
    maps.getPlayerBelongsToUs()->addUnit(std::make_shared<Swordsman>());
    maps.getPlayerBelongsToUs()->addUnit(std::make_shared<Worker>());


    maps.getPlayerBelongsToUs()->moveUnit(maps,4,{-5,-3});
    maps.getPlayerBelongsToUs()->moveUnit(maps,6,{11,4});

    maps.getPlayerBelongsToEnemy()->printObjectsOwn();
    std::cout<<"\n\n";
    maps.getPlayerBelongsToUs()->printObjectsOwn();


    return 0;
}