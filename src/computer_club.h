//
// Created by sergey on 17.05.24.
//

#ifndef YADRO_COMPUTER_CLUB_H
#define YADRO_COMPUTER_CLUB_H
#include <iostream>

class ComputerClub {
public:
    bool initConfig(std::istream &inputFile);


    int tableCount;
    int timeStart;
    int timeEnd;
    int hourlyRate;



private:
    bool initTables(std::string &line);
    bool initTime(std::string &line);
    bool initHourlyRate(std::string &line);



};


#endif //YADRO_COMPUTER_CLUB_H
