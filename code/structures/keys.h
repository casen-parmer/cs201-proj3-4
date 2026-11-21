/*
Shelbe Yousey, Casen Parmer, Riley Herchert - Dr. Don Yessick - Lucas Hasting
Defines comparator functors used for ordering Person, Doctor, and Patient pointers.
*/

#pragma once

#include "doctor.h"
#include "patient.h"
#include "person.h"

// Person by id for the records b-tree
struct PersonByID
{
    // Compares two Person pointers by ID ascending. Input: a, b Person pointers. Output: true if a->getID() < b->getID().
    bool operator()(Person *a, Person *b) const
    {
        return a->getID() < b->getID();
    }
};

// Doctor by skill for on-shift doctors
struct DoctorBySkill
{
    // Orders doctors with lower skill or smaller ID as lower priority. Input: a, b Doctor pointers. Output: true if a precedes b.
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
    // Orders doctors so earlier start times have higher heap priority. Input: a, b Doctor pointers. Output: true if a has lower priority than b.
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
struct PatientByArrival
{
    // Orders patients by earliest arrival, then higher condition, then ID. Input: a, b Patient pointers. Output: true if a has lower priority than b.
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