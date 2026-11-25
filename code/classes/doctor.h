/*
Shelbe Yousey, Casen Parmer, Riley Herchert - Dr. Don Yessick - Lucas Hasting
Defines the Doctor class with skill level, availability, and shift bounds.
*/

#pragma once

#include "person.h"

class Doctor : public Person
{

private:
    int skill;
    bool available;
    int startTime;
    int endTime;
    bool hired = true;

public:
    Doctor(std::string name, int age, std::string birthdate, int skill, bool available, int startTime, int endTime);
    int getSkill();
    bool isAvailable();
    bool isHired();
    void setHired(bool hire);
    void setAvailability(bool avail);
    int getStartTime();
    int getEndTime();
};
