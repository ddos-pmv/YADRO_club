#pragma once

#include <iostream>
#include <memory>
#include <string>

class ComputerClub;

/**
 * @class Event
 * @brief Base class for all events in the computer club.
 */
class Event {
 public:
  /**
   * @brief Constructor for the Event class.
   * @param time The time of the event in minutes.
   * @param detail Additional details about the event.
   * @param club Reference to the ComputerClub instance.
   */
  Event(int time, const std::string& detail, ComputerClub& club);

  /**
   * @brief Executes the event logic.
   */
  virtual void execute() = 0;

  /**
   * @brief Prints the event details.
   * @param out The output stream to print to (default is std::cout).
   */
  virtual void print(std::ostream& out = std::cout) const;

  /**
   * @brief Prints an error message related to the event.
   * @param errorMsg The error message to print.
   */
  void printError(const std::string& errorMsg) const;

  /**
   * @brief Virtual destructor for the Event class.
   */
  virtual ~Event() = default;

 protected:
  int time;           /**< The time of the event in minutes. */
  std::string detail; /**< Additional details about the event. */
  ComputerClub& club; /**< Reference to the ComputerClub instance. */
  int id;             /**< The unique identifier for the event type. */
};

using EventPtr = std::unique_ptr<Event>;

/**
 * @class ArrivalEvent
 * @brief Represents a client arrival event.
 */
class ArrivalEvent final : public Event {
 public:
  /**
   * @brief Constructor for the ArrivalEvent class.
   * @param time The time of the event in minutes.
   * @param detail The name of the client.
   * @param club Reference to the ComputerClub instance.
   */
  ArrivalEvent(int time, const std::string& detail, ComputerClub& club);

  /**
   * @brief Executes the arrival event logic.
   */
  void execute() override;
};

/**
 * @class SeatEvent
 * @brief Represents a client seating event.
 */
class SeatEvent final : public Event {
 public:
  /**
   * @brief Constructor for the SeatEvent class.
   * @param time The time of the event in minutes.
   * @param detail The name of the client.
   * @param tableId The ID of the table to seat the client at.
   * @param club Reference to the ComputerClub instance.
   */
  SeatEvent(int time, const std::string& detail, int tableId,
            ComputerClub& club);

  /**
   * @brief Executes the seating event logic.
   */
  void execute() override;

  /**
   * @brief Prints the seating event details.
   * @param out The output stream to print to (default is std::cout).
   */
  void print(std::ostream& out = std::cout) const override;

 private:
  int tableId; /**< The ID of the table to seat the client at. */
};

/**
 * @class WaitEvent
 * @brief Represents a client waiting event.
 */
class WaitEvent : public Event {
 public:
  /**
   * @brief Constructor for the WaitEvent class.
   * @param time The time of the event in minutes.
   * @param detail The name of the client.
   * @param club Reference to the ComputerClub instance.
   */
  WaitEvent(int time, const std::string& detail, ComputerClub& club);

  /**
   * @brief Executes the waiting event logic.
   */
  void execute() override;
};

/**
 * @class LeaveEvent
 * @brief Represents a client leaving event.
 */
class LeaveEvent final : public Event {
 public:
  /**
   * @brief Constructor for the LeaveEvent class.
   * @param time The time of the event in minutes.
   * @param detail The name of the client.
   * @param club Reference to the ComputerClub instance.
   */
  LeaveEvent(int time, const std::string& detail, ComputerClub& club);

  /**
   * @brief Executes the leaving event logic.
   */
  void execute() override;
};

/**
 * @class ExitEvent
 * @brief Represents a client exit event.
 */
class ExitEvent final : public Event {
 public:
  /**
   * @brief Constructor for the ExitEvent class.
   * @param time The time of the event in minutes.
   * @param detail The name of the client.
   * @param club Reference to the ComputerClub instance.
   */
  ExitEvent(int time, const std::string& detail, ComputerClub& club);

  /**
   * @brief Executes the exit event logic.
   */
  void execute() override;
};

/**
 * @class SeatInnerEvent
 * @brief Represents an internal seating event for waiting clients.
 */
class SeatInnerEvent final : public Event {
 public:
  /**
   * @brief Constructor for the SeatInnerEvent class.
   * @param time The time of the event in minutes.
   * @param detail The name of the client.
   * @param tableId The ID of the table to seat the client at.
   * @param club Reference to the ComputerClub instance.
   */
  SeatInnerEvent(int time, const std::string& detail, int tableId,
                 ComputerClub& club);

  /**
   * @brief Executes the internal seating event logic.
   */
  void execute() override;

  /**
   * @brief Prints the internal seating event details.
   * @param out The output stream to print to (default is std::cout).
   */
  void print(std::ostream& out = std::cout) const override;

 private:
  int tableId; /**< The ID of the table to seat the client at. */
};

/**
 * @class EventFactory
 * @brief Factory class for creating events.
 */
class EventFactory {
 public:
  /**
   * @brief Creates an event based on the input line.
   * @param line The input line describing the event.
   * @param club Reference to the ComputerClub instance.
   * @return A unique pointer to the created event.
   */
  static EventPtr createEvent(std::string& line, ComputerClub& club);
};