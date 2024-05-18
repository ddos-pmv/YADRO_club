//
// Created by sergey on 17.05.24.
//

#ifndef YADRO_COMPUTER_CLUB_H
#define YADRO_COMPUTER_CLUB_H
#include <iostream>
#include <algorithm>
#include <memory>
#include <set>
#include <map>
#include <queue>

class Event;

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

class ComputerClub {
public:
    bool initConfig(std::istream &inputFile);
    int getTableCount() const{return tableCount;};
    int getCurMaxTime() const {return curMaxTime;};
    void setCurMaxTime(int time){
        curMaxTime = std::max(curMaxTime, time);
    }
    void processEvents();
    void addEvent(std::unique_ptr<Event> event);
    int getTimeStart() const{ return timeStart;};
    int getTimeEnd() const{return timeEnd;};
    int getHourlyRate()const{return hourlyRate;};
    int getWaitingCount(){return (int)waitingClients.size();};
    int getOccupiedTables() {return occupiedTables;};
    int decOccupiedTables() {return --occupiedTables;};
    int incOccupiedTables() {return ++occupiedTables;};
    void addWaitingClient(std::string &name);
    bool isFreeTable();
    Client &getClient(std::string &name) {
        return clients[name];
    }
    Table &getTable(int tableId){
        return tables[tableId];
    }
    std::string &getFirstInQueue();
    void popQueue(){ waitingClients.pop();};


private:
    std::map<std::string,Client> clients;
    std::map<int,Table> tables;
    std::queue<std::string> waitingClients;
    std::vector<std::unique_ptr<Event>> events;

    int tableCount;
    int timeStart;
    int timeEnd;
    int hourlyRate;
    int curMaxTime = 0;
    int occupiedTables = 0;
    bool initTables(std::string &line);
    bool initTime(std::string &line);
    bool initHourlyRate(std::string &line);



};


#endif //YADRO_COMPUTER_CLUB_H
