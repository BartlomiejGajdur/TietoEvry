#include "../Include/FileManager.hpp"
#include <iostream>

FileManager::~FileManager(){
    if(file_.is_open())
        file_.close();
}

bool FileManager::openFile(){
    file_.open(fileName_);

    if(!file_.is_open())
    {
        std::cerr<<"Error while file opening: "<<fileName_<<"\n";
        return false;
    }

    return true;
}

bool FileManager::readFromFile(){
    if(!file_.is_open())
    {
        std::cerr<<"File is not open: "<<fileName_<<"\n";
        return false;
    }
    std::string line{};

    while(file_ >> line)
        fileContent_+=line +"\n";

    return true; 
}