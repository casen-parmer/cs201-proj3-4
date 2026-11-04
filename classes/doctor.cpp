// header comment

#ifndef DOCTOR_TPP
#define DOCTOR_TPP

#include "doctor.h"
#include "person.h"
#include "person.cpp"

class Doctor : public Person
{
    int condition;
};

#endif
