// header comment

#ifndef DOCTOR_H
#define DOCTOR_H

#include "patient.h"

class Doctor : public Person
{
private:
    int skill;
    bool available;
    int start_time;
    int end_time;
    Patient* patient;  // pointer to the patient they are treating
public:
    int getSkill() {
        return skill;
    }
    Patient* getPatient() {
        return patient;
    }
    bool isAvailable() {
        return available;
    }
    int getStartTime() const {
        return start_time;
    }
    int getEndTime() const {
        return end_time;
    }
    Doctor(std::string name, int age, std::string birthdate, int skill, bool available,
           int start_time, int end_time, Patient* patient = nullptr)
        : Person(name, age, birthdate), skill(skill), available(available),
          start_time(start_time), end_time(end_time), patient(patient) {}
};

#endif
