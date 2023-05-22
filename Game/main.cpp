#include <iostream>
#include "Include/FileManager.hpp"
#include <algorithm>
#include "Include/Coordinates.hpp"
#include "Include/Object.hpp"
#include "Include/map.hpp"
#include "Include/Units.hpp"
#include <memory>
int main(){

    // FileManager mapa("../Config/mapa.txt");
    // mapa.openFile();
    // mapa.readFromFile();
    // std::string line = mapa.getFileContent();

    // Map maps(line);

     Coordinates first{1,2};
    Coordinates second{2,3};

    std::shared_ptr<Base> basa = std::make_shared<Base>();
    std::shared_ptr<Knight> Knif = std::make_shared<Knight>(first,70);
    std::shared_ptr<Swordsman> miecznik2 = std::make_shared<Swordsman>(second,60);
    
    Knif->Attack(basa);
    miecznik2->Attack(basa);
    std::cout<<basa->getEndurance();

   

    //std::cout<<Coordinates::distance(first,second);
    return 0;
}