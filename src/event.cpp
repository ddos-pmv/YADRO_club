#include "event.h"

#include <iomanip>
#include <regex>
#include <sstream>

#include "computer_club.h"
#include "utils/exceptions.h"
#include "utils/parse_utils.h"

Event::Event(int time, const std::string& detail, ComputerClub& club)
    : time(time), detail(detail), club(club) {}

void Event::print(std::ostream& out) const {
  out << formatMinutes(time) << " " << id << " " << detail << '\n';
}

void Event::printError(const std::string& errorMsg) const {
  std::cout << formatMinutes(time) << " "
            << static_cast<int>(OutEventType::ERROR) << " " << errorMsg << '\n';
}

ArrivalEvent::ArrivalEvent(int time, const std::string& detail,
                           ComputerClub& club)
    : Event(time, detail, club) {
  id = 1;
}

void ArrivalEvent::execute() {
  Client& client = club.getClient(detail);
  if (client.inClub) {
    printError("YouShallNotPass");
    return;
  }
  if (time < club.timeStart() || time > club.timeEnd()) {
    printError("NotOpenYet");
    return;
  }
  client.inClub = true;
}

SeatEvent::SeatEvent(int time, const std::string& detail, int tableId,
                     ComputerClub& club)
    : Event(time, detail, club), tableId(tableId) {
  id = 2;
}

void SeatEvent::execute() {
  Client& client = club.getClient(detail);
  if (!client.inClub) {
    printError("ClientUnknown");
    return;
  }
  Table& table = club.getTable(tableId);
  if (table.occupiedNow) {
    printError("PlaceIsBusy");
    return;
  }
  club.incOccupiedTables();
  if (client.currentTable != 0) {
    Table& oldTable = club.getTable(client.currentTable);
    oldTable.occupiedMinutes += time - client.startTime;
    if (client.paidForTime < time) {
      oldTable.revenue +=
          club.hourlyRate() * ((time - client.startTime + 59) / 60);
      client.paidForTime =
          client.startTime + ((time - client.startTime + 59) / 60) * 60;
    }
    oldTable.occupiedNow = false;
    oldTable.currentClient.clear();
    club.decOccupiedTables();
  }
  client.startTime = time;
  client.currentTable = tableId;
  table.currentClient = detail;
  table.occupiedNow = true;
}

void SeatEvent::print(std::ostream& out) const {
  out << formatMinutes(time) << " " << id << " " << detail << " " << tableId
      << '\n';
}

WaitEvent::WaitEvent(int time, const std::string& detail, ComputerClub& club)
    : Event(time, detail, club) {
  id = 3;
}

void WaitEvent::execute() {
  Client& client = club.getClient(detail);
  if (!client.inClub) {
    printError("ClientUnknown");
    return;
  }
  if (club.getOccupiedTables() < club.tableCount()) {
    printError("ICanWaitNoLonger");
    return;
  }
  if (club.tableCount() <= club.getWaitingCount()) {
    EventPtr exitEvent = std::make_unique<ExitEvent>(time, detail, club);
    exitEvent->print();
    exitEvent->execute();
    return;
  }
  club.addWaitingClient(detail);
}

LeaveEvent::LeaveEvent(int time, const std::string& detail, ComputerClub& club)
    : Event(time, detail, club) {
  id = 4;
}

void LeaveEvent::execute() {
  Client& client = club.getClient(detail);
  if (!client.inClub) {
    printError("ClientUnknown");
    return;
  }
  if (client.currentTable != 0) {
    Table& oldTable = club.getTable(client.currentTable);
    oldTable.occupiedMinutes += time - client.startTime;
    if (client.paidForTime < time) {
      oldTable.revenue +=
          club.hourlyRate() * ((time - client.startTime + 59) / 60);
      client.paidForTime =
          client.startTime + ((time - client.startTime + 59) / 60) * 60;
    }
    oldTable.occupiedNow = false;
    oldTable.currentClient.clear();
    club.decOccupiedTables();

    int newFreeTable = client.currentTable;
    if (club.getWaitingCount() > 0) {
      std::string waitingClient = club.getFirstInQueue().value();
      club.popQueue();
      EventPtr seatInnerEvent = std::make_unique<SeatInnerEvent>(
          time, waitingClient, newFreeTable, club);
      seatInnerEvent->print();
      seatInnerEvent->execute();
    }
  }
  client.currentTable = 0;
  client.inClub = false;
}

ExitEvent::ExitEvent(int time, const std::string& detail, ComputerClub& club)
    : Event(time, detail, club) {
  id = 11;
}

void ExitEvent::execute() {
  Client& client = club.getClient(detail);
  client.inClub = false;
  if (client.currentTable != 0) {
    Table& oldTable = club.getTable(client.currentTable);
    oldTable.occupiedMinutes += time - client.startTime;
    if (client.paidForTime < time) {
      oldTable.revenue +=
          club.hourlyRate() * ((time - client.startTime + 59) / 60);
    }
    oldTable.occupiedNow = false;
    oldTable.currentClient.clear();
    club.decOccupiedTables();
  }
  client.currentTable = 0;
}

SeatInnerEvent::SeatInnerEvent(int time, const std::string& detail, int tableId,
                               ComputerClub& club)
    : Event(time, detail, club), tableId(tableId) {
  id = 12;
}

void SeatInnerEvent::execute() {
  Client& client = club.getClient(detail);
  Table& table = club.getTable(tableId);
  client.startTime = time;
  client.currentTable = tableId;
  table.currentClient = detail;
  table.occupiedNow = true;
  club.incOccupiedTables();
}

void SeatInnerEvent::print(std::ostream& out) const {
  out << formatMinutes(time) << " " << id << " " << detail << " " << tableId
      << '\n';
}

EventPtr EventFactory::createEvent(std::string& line, ComputerClub& club) {
  std::istringstream iss(line);
  int hours, minutes;
  char delim;
  int eventIdRaw;
  std::string clientName;
  if (!(iss >> hours >> delim >> minutes >> eventIdRaw) ||
      !validateTime(hours, minutes) ||
      club.getCurMaxTime() > toMinutes(hours, minutes)) {
    throw EventParseException(line);
  }

  const int time = toMinutes(hours, minutes);
  const InEventType eventId = static_cast<InEventType>(eventIdRaw);

  club.setCurMaxTime(time);
  if (!(iss >> clientName) || !validateName(clientName)) {
    throw EventParseException(line);
  }

  switch (eventId) {
    case InEventType::ARRIVAL:
      return std::make_unique<ArrivalEvent>(time, clientName, club);
    case InEventType::SEAT: {
      int tableId;
      if (!(iss >> tableId) || tableId < 1 || tableId > club.tableCount()) {
        throw EventParseException(line);
      }
      return std::make_unique<SeatEvent>(time, clientName, tableId, club);
    }
    case InEventType::WAIT:
      return std::make_unique<WaitEvent>(time, clientName, club);
    case InEventType::LEAVE:
      return std::make_unique<LeaveEvent>(time, clientName, club);
    default:
      throw EventParseException(line);
  }
}