#include <iostream>
#include "Include/FileManager.hpp"
#include <algorithm>
#include "Include/Coordinates.hpp"
#include "Include/MapObjects.hpp"
#include "Include/map.hpp"
#include "Include/Mediator.hpp"
#include "Include/Units.hpp"
#include "Include/Player.hpp"
#include "Include/Time.hpp"
#include <memory>



int main(int argc, char *argv[]) {
    int result = mediator::checkGivenData(argc, argv);
    if (result != 0) {
        // Wyświetl komunikat lub podejmij odpowiednie działania w przypadku błędu
        std::cout << "Error Occured. Program ends." << std::endl;
        return 1;
    }

    //Continue program
    FileManager File(file1_content);
    File.openFile();
    File.readFromFile();
    std::string line = File.getFileContent();

    Time czas{}; 
    Map maps(line,std::make_shared<Player>(),std::make_shared<Player>(),0);
    czas.addObserver(&maps);
    //maps.performAction();
    czas.nextRound();

    return 0;
}

