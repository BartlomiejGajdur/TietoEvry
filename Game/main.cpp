#include <iostream>
#include "Include/FileManager.hpp"
#include <algorithm>
#include "Include/Coordinates.hpp"
int main(){

    FileManager mapa("../Config/mapa.txt");
    mapa.openFile();
    mapa.readFromFile();
    std::cout<<mapa.getFileContent();

    std::string line = mapa.getFileContent();

    //Obliczanie rozmiaru mapy Trzeba pamietac ze rozpoczynamy od 0x0
    size_t SIZE_Y = std::count(line.begin(), line.end(), '\n');
    auto it = std::find(line.begin(),line.end(),'\n');
    size_t SIZE_X = std::distance(line.begin(),it);
    std::cout<< SIZE_X<<"x"<<SIZE_Y<<"\n";


    Coordinates first{1,2};
    Coordinates second{3,7};

    std::cout<<Coordinates::distance(first,second);
    return 0;
}