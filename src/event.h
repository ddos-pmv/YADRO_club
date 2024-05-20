//
// Created by sergey on 17.05.24.
//
#pragma once
#ifndef YADRO_EVENT_H
#define YADRO_EVENT_H

#include <iomanip>
#include <iostream>
#include <memory>

#include "computer_club.h"

class Event {
public:
    Event(int time, const std::string& detail, ComputerClub& club)
        : time(time), club(club), detail(detail) {};
    virtual void execute() = 0;
    virtual void print(std::ostream& out = std::cout) {
        out << std::setfill('0') << std::setw(2) << time / 60 << ":"
            << std::setfill('0') << std::setw(2) << time % 60 << " " << id
            << " " << detail << '\n';
    };
    void printError(const std::string& errorMsg) const {
        std::cout << std::setfill('0') << std::setw(2) << time / 60 << ":"
            << std::setfill('0') << std::setw(2) << time % 60 << " 13 "
            << errorMsg << '\n';
    }
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
    ArrivalEvent(int time, const std::string& detail, ComputerClub& club)
        : Event(time, detail, club) {
        id = 1;
    };
    void execute() override;
};
class SeatEvent : public Event {
public:
    SeatEvent(int time, const std::string& detail, int tableId,
        ComputerClub& club)
        : Event(time, detail, club), tableId(tableId) {
        id = 2;
    };
    void execute() override;
    void print(std::ostream& out = std::cout);

private:
    int tableId;
};

class WaitEvent : public Event {
public:
    WaitEvent(int time, const std::string& detail, ComputerClub& club)
        : Event(time, detail, club) {
        id = 3;
    };
    void execute() override;
};

class LeaveEvent : public Event {
public:
    LeaveEvent(int time, const std::string& detail, ComputerClub& club)
        : Event(time, detail, club) {
        id = 4;
    };
    void execute() override;
};

class ExitEvent : public Event {
public:
    ExitEvent(int time, const std::string& detail, ComputerClub& club)
        : Event(time, detail, club) {
        id = 11;
    };
    void execute() override;
};
class SeatInnerEvent : public Event {
public:
    SeatInnerEvent(int time, const std::string& detail, int tableId,
        ComputerClub& club)
        : Event(time, detail, club), tableId(tableId) {
        id = 12;
    };
    void execute() override;
    void print(std::ostream& out = std::cout);

private:
    int tableId;
};

class EventFactory {
public:
    static EventPtr createEvent(std::string& line, ComputerClub& club);

private:
    static bool validateTime(int hours, int minutes);
    static bool validateName(std::string& name);
};

#endif  // YADRO_EVENT_H
