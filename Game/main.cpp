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
    
    FileManager File(configLocalization);
    File.openFile();
    File.readFromFile();
    std::string line = File.getFileContent();

    Map maps(line,std::make_shared<Player>(),std::make_shared<Player>(),0);
    czas.addObserver(&maps);
    czas.nextRound();
    
    return 0;
}