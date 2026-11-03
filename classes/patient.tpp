// header comment

#ifndef PATIENT_TPP
#define PATIENT_TPP

#include "patient.h"
#include "person.h"
#include "person.cpp"

class Patient : public Person
{
private:
    int condition;
    PatientStatus status;
};

#endif
