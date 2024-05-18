#include <iostream>
#include <fstream>
#include <string>
#include "computer_club.h"
#include "event.h"
#include <memory>
#include <iomanip>

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

    bool formatError = false;
    std::string line;
    while(std::getline(inputFile, line)){
       EventPtr event = EventFactory::createEvent(line, club);
       if(!event){
           formatError = true;
           break;
       }
       club.addEvent(std::move(event));
    }

    if(!formatError){
        int startTime = club.getTimeStart();
        int endTime = club.getTimeEnd();
        std::cout<<std::setfill('0') << std::setw(2)<<startTime/60
        <<':'<<std::setfill('0') << std::setw(2)<<startTime%60<<'\n';

        club.processEvents();
        club.processClosing();
        club.printSummary();

        std::cout<<std::setfill('0') << std::setw(2)<<endTime/60
                 <<':'<<std::setfill('0') << std::setw(2)<<endTime%60<<'\n';
    }

    return 0;
}
