#include <iostream>
#include "Include/FileManager.hpp"
#include <algorithm>
#include "Include/Coordinates.hpp"
#include "Include/MapObjects.hpp"
#include "Include/map.hpp"
#include "Include/Units.hpp"
#include "Include/Player.hpp"
#include "Include/Time.hpp"
#include <memory>

std::string configLocalization ="../Config/mapa.txt";

int main(){
    Time czas{};
    
    FileManager File("../Config/mapa.txt");
    File.openFile();
    File.readFromFile();
    std::string line = File.getFileContent();

    Map maps(line,std::make_shared<Player>(),std::make_shared<Player>(),0);
    czas.addObserver(&maps);


    // maps.get_PlayerP()->addUnit(std::make_shared<Knight>(Coordinates(1,1),60));
    // maps.get_PlayerP()->addUnit(std::make_shared<Knight>(Coordinates(2,1),15));

    maps.get_PlayerE()->addUnit(std::make_shared<Knight>(Coordinates(2,2),60));


 
    std::cout<<"\nENEMY UNITS: \n";
    maps.get_PlayerE()->printObjectsOwn();
    std::cout<<"\n\n";

    maps.ProductAction_PlayerE(UnitTYPE::Knight);
   std::cout<< maps.get_PlayerE()->getMoney();
    czas.nextRound();
    czas.nextRound();
    czas.nextRound();
    maps.ProductAction_PlayerE(UnitTYPE::Knight);
    czas.nextRound();
    maps.ProductAction_PlayerE(UnitTYPE::Worker);
    czas.nextRound();
    czas.nextRound();
    czas.nextRound();
    czas.nextRound();
    // czas.nextRound();
    // czas.nextRound();

    std::cout<<"\nENEMY UNITS: \n";
    maps.get_PlayerE()->printObjectsOwn();
    std::cout<<"\n\n";
 

    return 0;
}