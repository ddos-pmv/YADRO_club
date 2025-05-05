#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

#include "computer_club.h"
#include "event.h"
#include "utils/exceptions.h"
#include "utils/parse_utils.h"
#include "utils/types.h"

int main(int argc, char* argv[]) {
  // check start options
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
    std::exit(-1);
  }

  std::string configPath = argv[1];

  try {
    // check if config file doesn't exists
    if (!std::filesystem::exists(configPath)) {
      throw std::runtime_error("Config file not found: " + configPath);
    }

    // try open config file
    std::ifstream file(configPath);
    if (!file.is_open()) {
      throw std::runtime_error("Failed to open config file: " + configPath);
    }

    ClubConfig clubConfig = parseClubConfig(file);

    ComputerClub club(clubConfig);

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
      // check if line consist only of spaces or /n
      if (!line.empty() &&
          std::find_if(line.begin(), line.end(), [](unsigned char c) {
            return !std::isspace(c);
          }) != line.end()) {
        EventPtr event = EventFactory::createEvent(line, club);
        if (!event) {
          throw EventParseException(line);
        }
        club.addEvent(std::move(event));
      }
    }

    std::cout << formatMinutes(club.timeStart()) << std::endl;
    club.processEvents();
    club.processClosing();
    std::cout << formatMinutes(club.timeEnd()) << std::endl;
    club.printSummary();

  } catch (const ParseException& e) {
    std::cerr << "Parse exception: " << e.what() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Unexpected err: " << e.what() << std::endl;
  }

  return 0;
}
