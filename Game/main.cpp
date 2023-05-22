#include <iostream>
#include "Include/FileManager.hpp"
#include <algorithm>
#include "Include/Coordinates.hpp"
#include "Include/Object.hpp"
#include "Include/map.hpp"
int main(){

    // FileManager mapa("../Config/mapa.txt");
    // mapa.openFile();
    // mapa.readFromFile();
    // std::string line = mapa.getFileContent();

    // Map maps(line);

     Coordinates first{1,2};
    Coordinates second{3,7};

    Unit Knif(UnitTYPE::Knight, 20,first );
    std::cout<<Knif.getObjectCoordinates()<<"\n";
    Knif.Move(second);
    std::cout<<Knif.getObjectCoordinates()<<"\n";
    std::cout<<Knif.getSpeedLeft()<<"\n";
    Knif.Move(Coordinates{12,8});
    std::cout<<Knif.getObjectCoordinates()<<"\n";
    std::cout<<Knif.getSpeedLeft()<<"\n";


   

    std::cout<<Coordinates::distance(first,second);
    return 0;
}