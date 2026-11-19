// header comment

#ifndef PATIENT_H
#define PATIENT_H

#include <optional>
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
    friend class Simulation;
private:
    int condition;
    PatientStatus status;
    std::optional<int> eta;  // eta of treatment being finished, if they are being treated
    int arrival_time;

public:
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
    }
};


#endif
