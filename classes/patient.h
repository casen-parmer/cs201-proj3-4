// header comment

#ifndef PATIENT_H
#define PATIENT_H

enum class PatientStatus
{
    WAITING,
    IN_VISIT,
    DISCHARGED
};

class Patient : Person
{
private:
    int condition;
    PatientStatus status;
};

#include "patient.tpp"

#endif
