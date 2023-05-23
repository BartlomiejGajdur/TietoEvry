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

    Map maps(line);
    Player Player{2000};

    //Player.moveUnit(maps,10,Coordinates{1,2});

    return 0;
}