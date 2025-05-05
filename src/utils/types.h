#pragma once
#include <string>

struct ClubConfig {
  int tableCount = 0;
  int timeStart = 0;
  int timeEnd = 0;
  int hourlyRate = 0;
};

struct Table {
  bool occupiedNow = false;
  int occupiedMinutes = 0;
  int revenue = 0;
  std::string currentClient;
};
struct Client {
  std::string name;
  bool inClub = false;
  int startTime = 0;
  int currentTable = 0;
  int paidForTime = 0;
};

enum class INPUT_EVENT { ARRIVAL = 1, SEAT = 2, WAIT = 3, LEAVE = 4 };
enum class OUTPUT_EVENT { LEAVE = 11, SEAT = 12, ERROR = 13 };

using InEventType = INPUT_EVENT;
using OutEventType = OUTPUT_EVENT;
