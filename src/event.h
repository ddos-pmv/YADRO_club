#pragma once

#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

#include "utils/types.h"

class ComputerClub;

class Event {
 public:
  Event(int time, const std::string& detail, ComputerClub& club);
  virtual void execute() = 0;
  virtual void print(std::ostream& out = std::cout) const;
  void printError(const std::string& errorMsg) const;
  virtual ~Event() = default;

 protected:
  int time;
  std::string detail;
  ComputerClub& club;
  int id;
};

using EventPtr = std::unique_ptr<Event>;

class ArrivalEvent : public Event {
 public:
  ArrivalEvent(int time, const std::string& detail, ComputerClub& club);
  void execute() override;
};

class SeatEvent : public Event {
 public:
  SeatEvent(int time, const std::string& detail, int tableId,
            ComputerClub& club);
  void execute() override;
  void print(std::ostream& out = std::cout) const override;

 private:
  int tableId;
};

class WaitEvent : public Event {
 public:
  WaitEvent(int time, const std::string& detail, ComputerClub& club);
  void execute() override;
};

class LeaveEvent : public Event {
 public:
  LeaveEvent(int time, const std::string& detail, ComputerClub& club);
  void execute() override;
};

class ExitEvent : public Event {
 public:
  ExitEvent(int time, const std::string& detail, ComputerClub& club);
  void execute() override;
};

class SeatInnerEvent : public Event {
 public:
  SeatInnerEvent(int time, const std::string& detail, int tableId,
                 ComputerClub& club);
  void execute() override;
  void print(std::ostream& out = std::cout) const override;

 private:
  int tableId;
};

class EventFactory {
 public:
  static EventPtr createEvent(std::string& line, ComputerClub& club);
};