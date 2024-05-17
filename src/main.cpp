#include <iostream>
#include <fstream>
#include <string>
#include "computer_club.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    ComputerClub club{};

    if(!club.initConfig(inputFile)){
        return 1;
    };

    std::string line;
//    while(std::getline(inputFile, line)){
//        auto event = EventFactory::createEvent(line);
//    }


    return 0;
}
