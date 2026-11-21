/*
Shelbe Yousey, Casen Parmer, Riley Herchert - Dr. Don Yessick - Lucas Hasting
Implements the Patient class constructor, getters, and treatment state updates.
*/

#include "patient.h"

// Constructs a Patient with no assigned ETA. Input: name, age, birthdate, condition, arrivalTime. Output: N/A.
Patient::Patient(std::string name, int age, std::string birthdate, int condition, int arrivalTime) : Person(name, age, birthdate), condition(condition), status(PatientStatus::SCHEDULED), eta(-1), arrivalTime(arrivalTime) {}

// Begins treatment by recording completion ETA and setting status to IN_VISIT. Input: eta minute. Output: N/A.
void Patient::seeDoctor(int eta)
{
    this->eta = eta;
    updateStatus(PatientStatus::IN_VISIT);
}

// Returns the patient's current status. Input: N/A. Output: PatientStatus enum value.
PatientStatus Patient::getStatus()
{
    return status;
}

// Returns the estimated completion time of treatment. Input: N/A. Output: eta minute, or -1 if unset.
int Patient::getETA()
{
    return eta;
}

// Returns the patient's arrival time in minutes. Input: N/A. Output: arrivalTime integer.
int Patient::getArrivalTime()
{
    return arrivalTime;
}

// Returns the patient's condition severity. Input: N/A. Output: condition integer.
int Patient::getCondition()
{
    return condition;
}

// Updates the patient's status. Input: newStat PatientStatus. Output: N/A.
void Patient::updateStatus(PatientStatus newStat)
{
    status = newStat;
}
