//
// Created by sergey on 17.05.24.
//
#include "computer_club.h"
#include "event.h"
#include <sstream>
#include <string>
#include <iostream>

bool ComputerClub::initConfig(std::istream &inputFile) {
    std::string line = "";
    if(!std::getline(inputFile, line) || !initTables(line)){
        std::cout<<line;
        return false;
    };
    if(!(std::getline(inputFile,line)) || !initTime(line)){
        std::cout<<line<<'\n';
        return false;
    }
    if(!(std::getline(inputFile,line)) || !initHourlyRate(line)){
        std::cout<<line<<'\n';
        return false;
    }
    return true;

}


bool ComputerClub::initTables(std::string &line) {
    std::istringstream iss(line);
    if(!(iss>>tableCount) || tableCount<0 ) return false;
    return true;
}

bool ComputerClub::initTime(std::string &line) {
    std::istringstream iss(line);
    char delim;
    int hours , minutes;

    if(!(iss>>hours>>delim>>minutes) || hours<0 || hours>24 || minutes>60 || minutes<0 || (hours==24 && minutes>0)) {
        std::cout<<line;
        return false;
    }
    timeStart = hours*60 + minutes;

    if(!(iss>>hours>>delim>>minutes) ||hours<0 || hours>24 || minutes>60 || minutes<0 || (hours==24 && minutes>0)|| (hours*60 + minutes<timeStart)){
        std::cout<<line;
        return false;
    }
    timeEnd =  hours*60+minutes;
    return true;
}

bool ComputerClub::initHourlyRate(std::string &line) {
    std::istringstream iss(line);
    if(!(iss>>hourlyRate) || hourlyRate<0){
        std::cout<<line;
        return false;
    }
    return true;
}

void ComputerClub::addEvent(std::unique_ptr<Event> event) {
    events.push_back(std::move(event));
}

void ComputerClub::processEvents() {
    for(auto &event :events){
        event->print();
        event->execute();
    }
}

void ComputerClub::addWaitingClient(std::string &name) {
    waitingClients.emplace(name);
}

std::string &ComputerClub::getFirstInQueue() {
    return waitingClients.front();
}

void ComputerClub::printSummary() {
    for(int i= 1;i<=tableCount;i++){
        std::cout<<i<<" "<<tables[i].revenue<<" "
        <<std::setfill('0') << std::setw(2)<<tables[i].occupiedMinutes/60
        <<":"<<std::setfill('0') << std::setw(2)<<tables[i].occupiedMinutes%60<<'\n';
    }

}

void ComputerClub::processClosing() {
    for(auto &[key, client]:clients){
        if(client.inClub){
            EventPtr exitEvent = std::make_unique<ExitEvent>(timeEnd, key, *this);
            exitEvent->print();
            exitEvent->execute();
        }
    }
}







