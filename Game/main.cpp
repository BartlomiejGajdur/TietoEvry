#include <iostream>
#include "Include/FileManager.hpp"
int main(){

    FileManager mapa("../Config/mapa.txt");
    mapa.openFile();
    mapa.readFromFile();
    std::cout<<mapa.getFileContent();

    return 0;
}