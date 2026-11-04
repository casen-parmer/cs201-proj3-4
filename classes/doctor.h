// header comment

#ifndef DOCTOR_H
#define DOCTOR_H

#include "person.h"

class Doctor : public Person
{
private:
    bool available;
    int start_time;
    int end_time;
public:
    bool isAvailable() const;
    int getStartTime() const;
    int getEndTime() const;
    Doctor(bool available, int start_time, int end_time);
};

#endif
