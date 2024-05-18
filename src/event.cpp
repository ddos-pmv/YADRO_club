//
// Created by sergey on 17.05.24.
//

#include "event.h"
#include "computer_club.h"
#include <sstream>
#include <regex>
#include <iomanip>


void SeatEvent::print(std::ostream &out){
    out<<std::setfill('0') << std::setw(2)<<time/60
       <<":"<<std::setfill('0') << std::setw(2)<<time%60<<" "<<id<<" "<<detail<<" "<<tableId<<'\n';
};
void SeatInnerEvent::print(std::ostream &out) {
    out<<std::setfill('0') << std::setw(2)<<time/60
    <<":"<<std::setfill('0') << std::setw(2)<<time%60<<" "<<id<<" "<<detail<<" "<<tableId<<'\n';
}



bool EventFactory::validateTime(int hours, int minutes) {
    return hours>=0 and minutes>=0 and hours<25 and minutes<61 and (minutes==0 and hours==24 || hours<24);
}
bool EventFactory::validateName(std::string &name) {
    std::regex pattern("^[a-z0-9_-]+$");
    return std::regex_match(name, pattern);
}

EventPtr EventFactory::createEvent(std::string &line, ComputerClub &club) {
    std::istringstream iss(line);
    int time;
    int hours, minutes;
    char delim;
    int eventId;
    std::string clientName;
    if(!(iss>>hours>>delim>>minutes>>eventId) || !validateTime(hours, minutes) and club.getCurMaxTime()<=hours*60+minutes){
        std::cout<<line<<'\n';
        return nullptr;
    }

    time = hours*60+minutes;
    club.setCurMaxTime(time);
    if(!(iss>>clientName)|| !validateName(clientName)){
        std::cout<<line<<'\n';
        return nullptr;
    }
    int tableId;
    switch (eventId) {
        case 1:
            return std::make_unique<ArrivalEvent>(time, clientName, club);
        case 2:
            iss>>tableId;
            if(tableId<1 || tableId>club.getTableCount()){
                std::cout<<line<<'\n';
                return nullptr;
            }
            return std::make_unique<SeatEvent>(time, clientName, tableId, club);
        case 3:
            return  std::make_unique<WaitEvent>(time, clientName,club);
        case 4:
            return std::make_unique<LeaveEvent>(time,clientName, club);
        default:
            std::cout<<line<<'\n';
    }
    return nullptr;

}


void ArrivalEvent::execute() {
    Client &client = club.getClient(detail);
    if (client.inClub) {
        printError("YouShallNotPass");
        return;
    }
    if (time < club.getTimeStart() || time>club.getTimeEnd()) {
        printError("NotOpenYet");
        return;
    }
    client.inClub = true;
}
void SeatEvent::execute() {
    Client& client = club.getClient(detail);
    if (!client.inClub) {
        printError("ClientUnknown");
        return;
    }
    Table &table = club.getTable(tableId);
    if(table.occupiedNow){
        printError("PlaceIsBusy");
        return;
    }
    club.incOccupiedTables();
    if(client.currentTable!=0){
        Table &oldTable = club.getTable(client.currentTable);
        oldTable.occupiedMinutes += time - client.startTime;
        if(client.paidForTime < time){
            oldTable.revenue += club.getHourlyRate() * ((time - client.startTime + 59) / 60);
            client.paidForTime = client.startTime + ((time - client.startTime + 59) / 60) * 60;
        }
        oldTable.occupiedNow = false;
        oldTable.currentClient.clear();
        club.decOccupiedTables();

    }
    client.startTime = time;
    client.currentTable = tableId;
    table.currentClient = detail;
    table.occupiedNow = true;
};
void WaitEvent::execute() {
    Client & client = club.getClient(detail);
    if (!client.inClub) {
        printError("ClientUnknown");
        return;
    }
    if(club.getOccupiedTables()<club.getTableCount()){
        printError("ICanWaitNoLonger");
        return;
    }
    if(club.getTableCount() <= club.getWaitingCount() ){
        EventPtr exitEvent = std::make_unique<ExitEvent>(time, detail, club);
        exitEvent->print();
        exitEvent->execute();
        return;
    }
    club.addWaitingClient(detail);

};
void LeaveEvent::execute() {
    Client & client = club.getClient(detail);
    if (!client.inClub) {
        printError("ClientUnknown");
        return;
    }
    if(client.currentTable!=0) {
        Table &oldTable = club.getTable(client.currentTable);
        oldTable.occupiedMinutes += time - client.startTime;
        if (client.paidForTime < time) {
            oldTable.revenue += club.getHourlyRate() * ((time - client.startTime + 59) / 60);
            client.paidForTime = client.startTime + ((time - client.startTime + 59) / 60) * 60;
        }
        oldTable.occupiedNow = false;
        oldTable.currentClient.clear();
        club.decOccupiedTables();


        client.inClub = false;
        int newFreeTable = client.currentTable;
        if (club.getWaitingCount() >0) {
            std::string waitingClient = club.getFirstInQueue();
            club.popQueue();
            EventPtr seatInnerEvent = std::make_unique<SeatInnerEvent>(time, waitingClient, newFreeTable, club);
            seatInnerEvent->print();
            seatInnerEvent->execute();
        }
    }
    client.currentTable = 0;

};


void ExitEvent::execute() {
    Client & client = club.getClient(detail);
    client.inClub = false;
    if(client.currentTable!=0){
        Table &oldTable = club.getTable(client.currentTable);
        oldTable.occupiedMinutes += time - client.startTime;
        if(client.paidForTime < time){
            oldTable.revenue += club.getHourlyRate() * ((time - client.startTime + 59) / 60);
        }
        oldTable.occupiedNow = false;
        oldTable.currentClient.clear();
        club.decOccupiedTables();
    }
    client.currentTable = 0;

}


void SeatInnerEvent::execute() {
    Client& client = club.getClient(detail);
    Table &table = club.getTable(tableId);
    client.startTime = time;
    client.currentTable = tableId;
    table.currentClient = detail;
    table.occupiedNow = true;
    club.incOccupiedTables();
}

