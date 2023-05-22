#include <iostream>
#include "Include/FileManager.hpp"
#include <algorithm>
#include "Include/Coordinates.hpp"
#include "Include/MapObjects.hpp"
#include "Include/map.hpp"
#include "Include/Units.hpp"
#include <memory>

std::array<std::array<unsigned short, 8>, 7> attackTable2{{
    {35, 35, 35, 35, 35, 50, 35, 1000},
    {30, 30, 30, 20, 20, 30, 30, 30},
    {15, 15, 15, 15, 10, 10, 15, 15},
    {35, 15, 15, 15, 15, 10, 15, 10},
    {40, 40, 40, 40, 40, 40, 40, 50},
    {10, 10, 10, 10, 10, 10, 10, 50},
    {5, 5, 5, 5, 5, 5, 5, 1}
}};


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
    std::shared_ptr<Worker> worker = std::make_shared<Worker>();
    
    Knif->Attack(basa);
    //miecznik2->Attack(basa);
    std::cout<<worker->getEndurance()<<"\n";
    miecznik2->Attack(worker);
    std::cout<<worker->getEndurance()<<"\n";
    miecznik2->Attack(worker);
    std::cout<<worker->getEndurance()<<"\n";
    std::cout<<basa->getEndurance();
    std::cout<<Knif->getId();
    std::cout<<miecznik2->getId();
    std::cout<<basa->getId()<<"\n";

    std::cout<<attackTable2[4][2];
   

    //std::cout<<Coordinates::distance(first,second);
    return 0;
}