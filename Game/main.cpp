#include <iostream>
#include "Include/FileManager.hpp"
#include <algorithm>
#include "Include/Coordinates.hpp"
#include "Include/map.hpp"
int main(){

    FileManager mapa("../Config/mapa.txt");
    mapa.openFile();
    mapa.readFromFile();
    std::string line = mapa.getFileContent();

    Map maps(line);




    Coordinates first{1,2};
    Coordinates second{3,7};

    std::cout<<Coordinates::distance(first,second);
    return 0;
}