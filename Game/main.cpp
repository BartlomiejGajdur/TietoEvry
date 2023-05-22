#include <iostream>
#include "Include/FileManager.hpp"
#include <algorithm>
#include "Include/Coordinates.hpp"
#include "Include/MapObjects.hpp"
#include "Include/map.hpp"
#include "Include/Units.hpp"
#include <memory>

std::string configLocalization ="../Config/mapa.txt";


int main(){

    FileManager mapa("../Config/mapa.txt");
    mapa.openFile();
    mapa.readFromFile();
    std::string line = mapa.getFileContent();

    Map maps(line);
    //maps.matchCoordinatesWithFile();

    return 0;
}