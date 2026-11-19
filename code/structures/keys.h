// header comment

#pragma once

#include "doctor.h"
#include "patient.h"

// Doctor by skill for on-shift doctors
struct DoctorBySkill
{
    bool operator()(Doctor *a, Doctor *b) const
    {
        if (a->getSkill() != b->getSkill())
        {
            return a->getSkill() < b->getSkill();
        }
        return a->getID() < b->getID(); // tiebreaker
    }
};

// Doctor by start time for off-shift doctors
struct DoctorByStartTime
{
    bool operator()(Doctor *a, Doctor *b) const
    {
        if (a->getStartTime() != b->getStartTime())
        {
            return a->getStartTime() > b->getStartTime();
        }
        return a->getID() < b->getID(); // tiebreaker
    }
};

// Patient by arrival time, condition as first tiebreaker, id as second tiebreaker
struct PatientByArrivalTime
{
    bool operator()(Patient *a, Patient *b) const
    {
        if (a->getArrivalTime() != b->getArrivalTime())
        {
            return a->getArrivalTime() > b->getArrivalTime();
        }
        if (a->getCondition() != b->getCondition()) // first tiebreaker
        {
            return a->getCondition() < b->getCondition();
        }
        return a->getID() < b->getID(); // second tiebreaker
    }
};