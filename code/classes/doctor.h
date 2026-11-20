// header comment

#pragma once

#include "person.h"

class Doctor : public Person
{
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
