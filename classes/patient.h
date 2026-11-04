// header comment

#ifndef PATIENT_H
#define PATIENT_H

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

public:
    Patient(std::string name, int age, std::string birthdate, int condition, PatientStatus status)
        : Person(name, age, birthdate), condition(condition), status(status) {}

    int getCondition() {
        return condition;
    }

    PatientStatus getStatus() {
        return status;
    }
};


#endif
