// header comment

#pragma once

#include "person.h"

enum class PatientStatus
{
    SCHEDULED,
    WAITING,
    IN_VISIT,
    FAILED_TO_TREAT,
    DISCHARGED
};

class Patient : public Person
{
private:
    int condition;
    PatientStatus status;
    int eta; // eta of treatment being finished, if they are being treated
    int arrivalTime;

public:
    Patient(std::string name, int age, std::string birthdate, int condition, int arrivalTime);
    void seeDoctor(int eta);
    PatientStatus getStatus();
    int getETA();
    int getArrivalTime();
    int getCondition();
    void worsenCondition();
    void updateStatus(PatientStatus newStat);
};

/*
    Patient(std::string name, int age, std::string birthdate, int condition,
            PatientStatus status = PatientStatus::SCHEDULED, std::optional<int> eta = {},
            int arrival_time = 480)
        : Person(name, age, birthdate), condition(condition), status(status), eta(eta),
          arrival_time(arrival_time) {}

    std::optional<int> getEta() {
        return eta;
    }

    int getCondition() {
        return condition;
    }

    PatientStatus getStatus() {
        return status;
    }*/