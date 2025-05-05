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

/**
 * @class ComputerClub
 * @brief Represents a computer club that manages clients, tables, and events.
 */
class ComputerClub {
 public:
  /**
   * @brief Constructor for the ComputerClub class.
   * @param config Configuration of the club.
   */
  explicit ComputerClub(const ClubConfig& config);

  /**
   * @brief Processes all events in the club.
   */
  void processEvents();

  /**
   * @brief Adds an event to the event queue.
   * @param event A unique pointer to the event.
   */
  void addEvent(std::unique_ptr<Event> event);

  /**
   * @brief Adds a client to the waiting queue.
   * @param name Name of the client.
   */
  void addWaitingClient(const std::string& name);

  /**
   * @brief Retrieves the first client in the waiting queue.
   * @return The name of the first client or std::nullopt if the queue is empty.
   */
  std::optional<std::string> getFirstInQueue() const;

  /**
   * @brief Removes the first client from the waiting queue.
   */
  void popQueue();

  /**
   * @brief Prints a summary of the club's revenue and table usage.
   */
  void printSummary();

  /**
   * @brief Processes the closing of the club, ensuring all clients leave.
   */
  void processClosing();

  // Getters

  /**
   * @brief Gets the total number of tables in the club.
   * @return The number of tables.
   */
  int tableCount() const;

  /**
   * @brief Gets the current maximum time of processed events.
   * @return The current maximum time.
   */
  int getCurMaxTime() const;

  /**
   * @brief Gets the club's opening time.
   * @return The opening time in minutes.
   */
  int timeStart() const;

  /**
   * @brief Gets the club's closing time.
   * @return The closing time in minutes.
   */
  int timeEnd() const;

  /**
   * @brief Gets the hourly rate of the club.
   * @return The hourly rate.
   */
  int hourlyRate() const;

  /**
   * @brief Gets the number of clients in the waiting queue.
   * @return The number of waiting clients.
   */
  int getWaitingCount() const;

  /**
   * @brief Gets the number of currently occupied tables.
   * @return The number of occupied tables.
   */
  int getOccupiedTables() const;

  /**
   * @brief Retrieves a reference to a client by name.
   * @param name The name of the client.
   * @return A reference to the client.
   */
  Client& getClient(const std::string& name);

  /**
   * @brief Retrieves a reference to a table by its ID.
   * @param tableId The ID of the table.
   * @return A reference to the table.
   */
  Table& getTable(int tableId);

  // Setters

  /**
   * @brief Sets the current maximum time of processed events.
   * @param time The new maximum time.
   */
  void setCurMaxTime(int time);

  /**
   * @brief Decreases the count of occupied tables.
   * @return The updated count of occupied tables.
   */
  int decOccupiedTables();

  /**
   * @brief Increases the count of occupied tables.
   * @return The updated count of occupied tables.
   */
  int incOccupiedTables();

 private:
  std::map<std::string, Client> clients; /**< Map of clients by name. */
  std::map<int, Table> tables; /**< Map of tables by ID. */
  std::queue<std::string> waitingClients; /**< Queue of waiting clients. */
  std::vector<std::unique_ptr<Event>> events; /**< List of events. */

  int curMaxTime = 0; /**< Current maximum time of processed events. */
  int occupiedTables = 0; /**< Number of currently occupied tables. */
  ClubConfig m_config; /**< Configuration of the club. */
};