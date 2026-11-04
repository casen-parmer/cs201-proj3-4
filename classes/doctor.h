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
    bool isAvailable() {
        return available;
    }
    int getStartTime() const {
        return start_time;
    }
    int getEndTime() const {
        return end_time;
    }
    Doctor(bool available, int start_time, int end_time);
};

#endif
