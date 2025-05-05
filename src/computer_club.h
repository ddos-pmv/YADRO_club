#pragma once

#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils/types.h"

class Event;

class ComputerClub {
 public:
  explicit ComputerClub(const ClubConfig& config);

  void processEvents();
  void addEvent(std::unique_ptr<Event> event);
  void addWaitingClient(const std::string& name);
  std::optional<std::string> getFirstInQueue() const;
  void popQueue();
  void printSummary();
  void processClosing();

  // Getters
  int tableCount() const;
  int getCurMaxTime() const;
  int timeStart() const;
  int timeEnd() const;
  int hourlyRate() const;
  int getWaitingCount() const;
  int getOccupiedTables() const;
  Client& getClient(const std::string& name);
  Table& getTable(int tableId);

  // Setters
  void setCurMaxTime(int time);
  int decOccupiedTables();
  int incOccupiedTables();

 private:
  std::map<std::string, Client> clients;
  std::map<int, Table> tables;
  std::queue<std::string> waitingClients;
  std::vector<std::unique_ptr<Event>> events;

  int curMaxTime = 0;
  int occupiedTables = 0;
  ClubConfig m_config;
};