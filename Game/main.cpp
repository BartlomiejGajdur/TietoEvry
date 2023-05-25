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

    FileManager File("../Config/mapa.txt");
    File.openFile();
    File.readFromFile();
    std::string line = File.getFileContent();

    Map maps(line,std::make_shared <Player>(),std::make_shared  <Player>());

    maps.get_PlayerP()->addUnit(std::make_shared<Knight>(Coordinates(1,1),60));
    maps.get_PlayerP()->addUnit(std::make_shared<Knight>(Coordinates(2,1),15));

    maps.get_PlayerE()->addUnit(std::make_shared<Knight>(Coordinates(2,2),60));


    std::cout<<"\nPLAYER UNITS: \n";
    maps.get_PlayerP()->printObjectsOwn();

    std::cout<<"\nENEMY UNITS: \n";
    maps.get_PlayerE()->printObjectsOwn();
    std::cout<<"\n\n";

    maps.get_PlayerE()->getUnits()[1]->Produce(UnitTYPE::Knight);

    maps.AttackAction_PlayerE(4,3);

    std::cout<<"\nPLAYER UNITS: \n";
    maps.get_PlayerP()->printObjectsOwn();

    return 0;
}