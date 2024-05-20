#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

#include "computer_club.h"
#include "event.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_name>" << std::endl;
        std::cerr << "input file must be placed in YADRO/data/..";
        return 1;
    }

    std::string filePath = std::string(DATA_DIR) + "/" + argv[1];
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        std::cerr << "Input file must be placed in YADRO/data/..";
        return 1;
    }

    ComputerClub club{};

    // parse 3 lines
    if (!club.initConfig(inputFile)) {
        return 1;
    };

    bool formatError = false;
    std::string line;

    // validate input data and parse it to events
    while (std::getline(inputFile, line)) {
        // check if line consist only of spaces or /n
        if (!line.empty() &&
            std::find_if(line.begin(), line.end(), [](unsigned char c) {
                return !std::isspace(c);
                }) != line.end()) {
            EventPtr event = EventFactory::createEvent(line, club);
            if (!event) {
                formatError = true;
                break;
            }
            club.addEvent(std::move(event));
        }
    }

    if (!formatError) {
        int startTime = club.getTimeStart();
        int endTime = club.getTimeEnd();
        // print start time
        std::cout << std::setfill('0') << std::setw(2) << startTime / 60 << ':'
            << std::setfill('0') << std::setw(2) << startTime % 60
            << '\n';

        club.processEvents();
        club.processClosing();

        // print end time
        std::cout << std::setfill('0') << std::setw(2) << endTime / 60 << ':'
            << std::setfill('0') << std::setw(2) << endTime % 60 << '\n';
        club.printSummary();
    }

    int a;
    std::cin >> a;

    return 0;
}
