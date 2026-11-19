// header comment

#include "patient.h"

Patient::Patient(std::string name, int age, std::string birthdate, int condition, int arrivalTime) : Person(name, age, birthdate), condition(condition), status(PatientStatus::SCHEDULED), eta(-1), arrivalTime(arrivalTime) {}

void Patient::seeDoctor(int eta)
{
    this->eta = eta;
    updateStatus(PatientStatus::IN_VISIT);
}

PatientStatus Patient::getStatus()
{
    return status;
}

int Patient::getETA()
{
    return eta;
}

int Patient::getArrivalTime()
{
    return arrivalTime;
}

int Patient::getCondition()
{
    return condition;
}

void Patient::worsenCondition()
{
    condition++;
    if (condition == 10)
    {
        updateStatus(PatientStatus::FAILED_TO_TREAT);
    }
}

void Patient::updateStatus(PatientStatus newStat)
{
    status = newStat;
}
