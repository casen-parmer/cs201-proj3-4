// header comment

#include "doctor.h"

Doctor::Doctor(std::string name, int age, std::string birthdate, int skill, bool available, int startTime, int endTime) : Person(name, age, birthdate), skill(skill), available(available), startTime(startTime), endTime(endTime) {}

int Doctor::getSkill()
{
    return skill;
}

bool Doctor::isAvailable()
{
    return available;
}

void Doctor::setAvailability(bool avail)
{
    available = avail;
}

int Doctor::getStartTime()
{
    return startTime;
}

int Doctor::getEndTime()
{
    return endTime;
}