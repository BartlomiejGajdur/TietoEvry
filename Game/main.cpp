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

    maps.getPlayerBelongsToUs()->addUnit(std::make_shared<Knight>(Coordinates(1,1),60));
    maps.getPlayerBelongsToUs()->addUnit(std::make_shared<Knight>(Coordinates(2,1),15));

    maps.getPlayerBelongsToEnemy()->addUnit(std::make_shared<Knight>(Coordinates(2,2),60));


    std::cout<<"\nPLAYER UNITS: \n";
    maps.getPlayerBelongsToUs()->printObjectsOwn();

    std::cout<<"\nENEMY UNITS: \n";
    maps.getPlayerBelongsToEnemy()->printObjectsOwn();
    std::cout<<"\n\n";

    

    maps.performAttackByPlayerBelongsToEnemy(4,3);

    std::cout<<"\nPLAYER UNITS: \n";
    maps.getPlayerBelongsToUs()->printObjectsOwn();

    return 0;
}