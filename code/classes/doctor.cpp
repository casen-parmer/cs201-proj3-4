/*
Shelbe Yousey, Casen Parmer, Riley Herchert - Dr. Don Yessick - Lucas Hasting
Implements the Doctor class constructor, getters, and availability setter.
*/

#include "doctor.h"

// Constructs a Doctor with shift and skill attributes. Input: name, age, birthdate, skill, available, startTime, endTime. Output: N/A.
Doctor::Doctor(std::string name, int age, std::string birthdate, int skill, bool available, int startTime, int endTime) : Person(name, age, birthdate), skill(skill), available(available), startTime(startTime), endTime(endTime) {}

// Returns the doctor's skill rating. Input: N/A. Output: skill.
int Doctor::getSkill()
{
    return skill;
}

// Returns whether the doctor is available. Input: N/A. Output: availability boolean.
bool Doctor::isAvailable()
{
    return available;
}

// Returns whether the doctor is hired. Input: N/A. Output: hired boolean.
bool Doctor::isHired() {
    return hired;
}

// Updates the doctor's availability. Input: availability boolean. Output: N/A.
void Doctor::setAvailability(bool avail)
{
    available = avail;
}

// Returns the doctor's shift start time in minutes. Input: N/A. Output: startTime integer.
int Doctor::getStartTime()
{
    return startTime;
}

// Returns the doctor's shift end time in minutes. Input: N/A. Output: endTime integer.
int Doctor::getEndTime()
{
    return endTime;
}