//
// Created by sergey on 17.05.24.
//

#include "event.h"
#include "computer_club.h"
#include <sstream>
#include <regex>


void SeatEvent::print(std::ostream &out){
    out<<time/60<<" "<<time%60<<" "<<id<<" "<<detail<<" "<<tableId;
};


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
void SeatEvent::execute() {};
void WaitEvent::execute() {};
void LeaveEvent::execute() {};







