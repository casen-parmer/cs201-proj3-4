// header comment

#pragma once

#include "person.h"

/*
Shelbe Yousey, Casen Parmer, Riley Herchert - Dr. Don Yessick - Lucas Hasting

This header file defines the Doctor Class.
*/

class Doctor : public Person
{
    //declare private variables
private:
    int skill;
    bool available;
    int startTime;
    int endTime;

public:
    Doctor(std::string name, int age, std::string birthdate, int skill, bool available, int startTime, int endTime);
    int getSkill();
    bool isAvailable();
    void setAvailability(bool avail);
    int getStartTime();
    int getEndTime();
};
