#include <iostream>
#include <fstream>
#include <string>
#include "computer_club.h"
#include "event.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    int tableCount, hourlyRate;
    std::string startTime, endTime;
    inputFile >> tableCount >> startTime >> endTime >> hourlyRate;

    ComputerClub club(tableCount, startTime, endTime, hourlyRate);

    std::string line;
    std::getline(inputFile, line); // Consume the rest of the line after hourly rate

    while (std::getline(inputFile, line)) {
        auto event = EventFactory::createEvent(line, club);
        club.addEvent(std::move(event));
    }

    club.processEvents();
    club.printSummary(std::cout);

    return 0;
}
