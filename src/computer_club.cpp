#include "computer_club.h"

#include <iostream>
#include <optional>
#include <sstream>
#include <string>

#include "event.h"
#include "utils/parse_utils.h"
#include "utils/types.h"

ComputerClub::ComputerClub(const ClubConfig& config) : m_config(config) {}

void ComputerClub::processEvents() {
  for (auto& event : events) {
    event->print();
    event->execute();
  }
}

void ComputerClub::addEvent(std::unique_ptr<Event> event) {
  events.push_back(std::move(event));
}

void ComputerClub::addWaitingClient(const std::string& name) {
  waitingClients.emplace(name);
}

std::optional<std::string> ComputerClub::getFirstInQueue() const {
  if (waitingClients.empty()) {
    return std::nullopt;
  }
  return waitingClients.front();
}

void ComputerClub::popQueue() {
  if (!waitingClients.empty()) {
    waitingClients.pop();
  }
}

void ComputerClub::printSummary() {
  for (int i = 1; i <= m_config.tableCount; i++) {
    std::cout << i << " " << tables[i].revenue << " " << formatMinutes(tables[i].occupiedMinutes) << '\n';
  }
}

void ComputerClub::processClosing() {
  for (auto& [key, client] : clients) {
    if (client.inClub) {
      auto exitEvent =
          std::make_unique<ExitEvent>(m_config.timeEnd, key, *this);
      exitEvent->print();
      exitEvent->execute();
    }
  }
}

// Getters
int ComputerClub::tableCount() const { return m_config.tableCount; }

int ComputerClub::getCurMaxTime() const { return curMaxTime; }

int ComputerClub::timeStart() const { return m_config.timeStart; }

int ComputerClub::timeEnd() const { return m_config.timeEnd; }

int ComputerClub::hourlyRate() const { return m_config.hourlyRate; }

int ComputerClub::getWaitingCount() const {
  return static_cast<int>(waitingClients.size());
}

int ComputerClub::getOccupiedTables() const { return occupiedTables; }

Client& ComputerClub::getClient(const std::string& name) {
  return clients[name];
}

Table& ComputerClub::getTable(int tableId) { return tables[tableId]; }

// Setters
void ComputerClub::setCurMaxTime(int time) {
  curMaxTime = std::max(curMaxTime, time);
}

int ComputerClub::decOccupiedTables() { return --occupiedTables; }

int ComputerClub::incOccupiedTables() { return ++occupiedTables; }