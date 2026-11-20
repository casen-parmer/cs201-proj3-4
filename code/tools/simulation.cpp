// Hospital event processing, using the existing B-tree, doctor BST and patient priority queue.
#include "simulation.h"

#include <algorithm>
#include <memory>

Simulation::Simulation(int startTime) : time(startTime - 1), paired(true) {}

Simulation::Simulation() : time(480), paired(true) {}

// overloads in order to share person as b-tree type

void Simulation::addPerson(Patient patient)
{
    Patient *p = records.insert(std::make_unique<Patient>(std::move(patient)));
    if (p)
    {
        patientQueue.push(p);
    }
}

void Simulation::addPerson(Doctor doctor)
{
    Doctor *d = records.insert(std::make_unique<Doctor>(std::move(doctor)));
    if (d)
    {
        offShiftDoctors.push(d);
    }
}

// full step for testing

void Simulation::step()
{
    stepPhase();
    if (!paired)
    {
        stepPhase();
    }
}

// half-step for GUI

void Simulation::stepPhase()
{
    if (paired)
    {
        time++;
        dischargePatients();
        startShifts();
        paired = false;
    }
    else
    {
        createPairings();
        paired = true;
    }
}

void Simulation::dischargePatients()
{
    // loop through current pairings and discharge any completed visits
    for (auto it = currentPairings.begin(); it != currentPairings.end();)
    {
        Doctor *d = it->first;
        Patient *p = it->second;
        if (p->getETA() <= time)
        {
            p->updateStatus(PatientStatus::DISCHARGED);
            discharged.push_back(p);
            d->setAvailability(true);
            // re-add doctor if still on shift
            if (isOnShift(d))
            {
                shiftDoctors.insert(d);
            }
            it = currentPairings.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void Simulation::startShifts()
{
    while (!offShiftDoctors.empty() && offShiftDoctors.top()->getStartTime() <= time)
    {
        Doctor *d = offShiftDoctors.top();
        offShiftDoctors.pop();
        if (isOnShift(d))
        {
            shiftDoctors.insert(d);
        }
    }
}

void Simulation::createPairings()
{
    while (!patientQueue.empty() && patientQueue.top()->getArrivalTime() <= time)
    {
        Patient *p = patientQueue.top();
        // out of time
        if (time > p->getArrivalTime() + TIME_LIMIT)
        {
            patientQueue.pop();
            p->updateStatus(PatientStatus::FAILED_TO_TREAT);
            failed.push_back(p);
            continue;
        }
        // no free doctors
        if (shiftDoctors.empty())
        {
            break;
        }
        Doctor *d = shiftDoctors.max();
        shiftDoctors.remove(d);
        if (!isOnShift(d))
        {
            continue;
        }
        patientQueue.pop();
        d->setAvailability(false);
        p->seeDoctor(time + treatmentTime(p, d));
        currentPairings.push_back({d, p});
    }
}

bool Simulation::isOnShift(Doctor *d)
{
    return d->getStartTime() <= time && time < d->getEndTime();
}

int Simulation::treatmentTime(Patient *p, Doctor *d)
{
    return std::max(1, 10 + p->getCondition() - d->getSkill());
}

Patient *Simulation::findPatient(const std::string &name, int age, const std::string &birthdate)
{
    Person probe(name, age, birthdate);
    return records.searchAs<Patient>(&probe);
}

Doctor *Simulation::findDoctor(const std::string &name, int age, const std::string &birthdate)
{
    Person probe(name, age, birthdate);
    return records.searchAs<Doctor>(&probe);
}

int Simulation::getTime() { return time; }
bool Simulation::isPaired() { return paired; }

std::vector<Patient *> Simulation::getWaiting()
{
    std::vector<Patient *> waiting;
    for (Person *person : records.inorder())
    {
        Patient *p = dynamic_cast<Patient *>(person);
        if (p && p->getStatus() == PatientStatus::SCHEDULED && p->getArrivalTime() <= time)
        {
            waiting.push_back(p);
        }
    }
    std::sort(waiting.begin(), waiting.end(), [](Patient *a, Patient *b)
              { return PatientByArrival{}(b, a); });
    return waiting;
}

std::vector<Doctor *> Simulation::getDoctors()
{
    std::vector<Doctor *> doctors;
    for (Person *person : records.inorder())
    {
        if (Doctor *d = dynamic_cast<Doctor *>(person))
        {
            doctors.push_back(d);
        }
    }
    return doctors;
}

int Simulation::getUpcomingCount()
{
    int count = 0;
    for (Person *person : records.inorder())
    {
        Patient *p = dynamic_cast<Patient *>(person);
        if (p && p->getArrivalTime() > time)
        {
            count++;
        }
    }
    return count;
}

Patient *Simulation::patientOf(Doctor *d)
{
    for (auto &pairing : currentPairings)
    {
        if (pairing.first == d)
        {
            return pairing.second;
        }
    }
    return nullptr;
}

const std::vector<std::pair<Doctor *, Patient *>> &Simulation::getPairings() { return currentPairings; }
const std::vector<Patient *> &Simulation::getDischarged() { return discharged; }
const std::vector<Patient *> &Simulation::getFailed() { return failed; }

/*
#include "simulation.h"
#include "patient_heap.h"
#include "patient.h"
#include <algorithm>
#include <utility>

Simulation::Simulation(std::vector<Patient> patients, std::vector<Doctor> doctors, int start)
    : patients(std::move(patients)), doctors(std::move(doctors)), time(start)
{
    for (Patient &p : this->patients)
    {
        records.insert(&p, p.getId());
    }
    for (Doctor &d : this->doctors)
    {
        records.insert(&d, d.getId());
        doctor_tree.insert(new bst::Node(&d, d.skill));
    }
    update_arrivals();
    pair_and_close();
}

void Simulation::step()
{
    ++time;
    update_arrivals();
    pair_and_close();
    paired = true;
}

void Simulation::step_phase()
{
    if (paired)
    {
        ++time;
        update_arrivals();
        paired = false;
    }
    else
    {
        pair_and_close();
        paired = true;
    }
}

void Simulation::update_arrivals()
{
    for (Doctor &d : doctors)
    {
        if (d.patient && d.patient->eta.value() <= time)
        {
            d.patient->condition = 0;
            d.patient->status = PatientStatus::DISCHARGED;
            d.patient->eta.reset();
            d.patient = nullptr;
        }
        // Doctors will stay after their shift to finish treating a paitent
        d.available = !d.patient && d.start_time <= time && time < d.end_time;
    }

    for (Patient &p : patients)
    {
        if (p.status == PatientStatus::SCHEDULED && p.arrival_time <= time)
            p.status = PatientStatus::WAITING;
        else if (p.status == PatientStatus::WAITING && time > p.arrival_time && p.condition < 10 && (time - p.arrival_time) % 7 == 0)
            ++p.condition;
    }
}

void Simulation::pair_and_close()
{
    PatientHeap waiting;
    for (Patient &p : patients)
        if (p.status == PatientStatus::WAITING)
            waiting.push(&p);

    while (!waiting.empty())
    {
        Patient *p = waiting.top();
        waiting.pop();
        auto *node = doctor_tree.find_lowest_available_doctor(p->condition, time);
        if (!node)
            continue; // Skip if no doctor has high enough skill
        Doctor &d = *node->value;
        d.patient = p;
        d.available = false;
        p->status = PatientStatus::IN_VISIT;
        p->eta = time + std::max(1, 10 + p->condition - d.skill);
    }

    for (Patient &p : patients)
        if (p.status == PatientStatus::WAITING && p.condition == 10)
            p.status = PatientStatus::FAILED_TO_TREAT;
}
*/