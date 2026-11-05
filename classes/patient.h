// header comment

#ifndef PATIENT_H
#define PATIENT_H

#include <optional>
#include "person.h"

enum class PatientStatus
{
    WAITING,
    IN_VISIT,
    DISCHARGED
};

class Patient : public Person
{
private:
    int condition;
    PatientStatus status;
    std::optional<int> eta;  // eta of treatment being finished, if they are being treated

public:
    Patient(std::string name, int age, std::string birthdate, int condition, PatientStatus status, std::optional<int> eta = {})
        : Person(name, age, birthdate), condition(condition), status(status), eta(eta) {}

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
