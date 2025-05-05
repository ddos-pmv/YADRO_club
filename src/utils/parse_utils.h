#pragma once

#include <iomanip>
#include <regex>
#include <sstream>

#include "exceptions.h"
#include "types.h"

[[nodiscard]] inline ClubConfig parseClubConfig(std::istream& in) {
  ClubConfig config;
  std::string line;
  int h, m;
  char delim;

  // 1. Tables
  if (!std::getline(in, line)) throw ParseException("Missing table count line");
  std::istringstream(line) >> config.tableCount;
  if (config.tableCount <= 0) throw ConfigParseException("Invalid table count");

  // 2. Time
  if (!std::getline(in, line)) throw ConfigParseException("Missing time line");
  std::istringstream timeStream(line);
  if (!(timeStream >> h >> delim >> m) || delim != ':' || h < 0 || h > 24 ||
      m < 0 || m >= 60)
    throw ConfigParseException("Invalid start time format");
  config.timeStart = h * 60 + m;

  if (!(timeStream >> h >> delim >> m) || delim != ':' || h < 0 || h > 24 ||
      m < 0 || m >= 60)
    throw ConfigParseException("Invalid end time format");
  config.timeEnd = h * 60 + m;

  if (config.timeEnd <= config.timeStart)
    throw ConfigParseException("End time must be after start time");

  // 3. Coast
  if (!std::getline(in, line))
    throw ConfigParseException("Missing hourly rate line");
  std::istringstream(line) >> config.hourlyRate;
  if (config.hourlyRate < 0)
    throw ConfigParseException("Hourly rate must be >= 0");

  return config;
}

inline int parseTimeToMinutes(const std::string& timeStr) {
  std::istringstream iss(timeStr);
  int h, m;
  char delim;

  if (!(iss >> h >> delim >> m) || delim != ':' || h < 0 || h > 24 || m < 0 ||
      m > 59 || (h == 24 && m > 0))
    throw std::invalid_argument(timeStr + " - invalid time format");

  return h * 60 + m;
}

inline int toMinutes(int hourse, int mins) noexcept {
  return hourse * 60 + mins;
}

inline bool validateTime(int hours, int minutes) noexcept {
  return (hours >= 0 && minutes >= 0 && hours < 24 && minutes < 60);
}

inline bool validateName(std::string& name) noexcept {
  std::regex pattern("^[a-z0-9_-]+$");
  return std::regex_match(name, pattern);
}

inline int mins(int totalMinutes) noexcept { return totalMinutes % 60; }
inline int hours(int totalMinutes) noexcept { return totalMinutes / 60; }

inline std::string formatMinutes(int totalMinutes) noexcept {
  int h = totalMinutes / 60;
  int m = totalMinutes % 60;

  std::ostringstream oss;
  oss << std::setw(2) << std::setfill('0') << h << ":" << std::setw(2)
      << std::setfill('0') << m;
  return oss.str();
}
