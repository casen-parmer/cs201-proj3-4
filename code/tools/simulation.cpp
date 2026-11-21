/*
Shelbe Yousey, Casen Parmer, Riley Herchert - Dr. Don Yessick - Lucas Hasting
Implements Simulation event processing, doctor/patient pairing, and state queries.
*/

#include "simulation.h"

#include <algorithm>
#include <memory>

// Constructs a Simulation starting one minute before startTime. Input: startTime minute. Output: N/A.
Simulation::Simulation(int startTime) : time(startTime - 1), paired(true) {}

// Constructs a Simulation starting at minute 480 (8:00). Input: N/A. Output: N/A.
Simulation::Simulation() : time(480), paired(true) {}

// overloads in order to share person as b-tree type

// Adds a Patient to BTree records and the arrival queue if not already present. Input: patient value. Output: N/A.
void Simulation::addPerson(Patient patient)
{
    if (records.search(patient.getID()) != nullptr)
    {
        return;
    }
    Patient *p = new Patient(std::move(patient));
    records.insert(p, p->getID());
    patientQueue.push(p);
}

// Adds a Doctor to BTree records and the off-shift queue if not already present. Input: doctor value. Output: N/A.
void Simulation::addPerson(Doctor doctor)
{
    if (records.search(doctor.getID()) != nullptr)
    {
        return;
    }
    Doctor *d = new Doctor(std::move(doctor));
    records.insert(d, d->getID());
    offShiftDoctors.push(d);
}

// full step for testing

// Advances the simulation by one full minute (both phases). Input: N/A. Output: N/A.
void Simulation::step()
{
    stepPhase();
    if (!paired)
    {
        stepPhase();
    }
}

// half-step for GUI

// Alternates between advancing time/updates and pairing patients with doctors. Input: N/A. Output: N/A.
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

// Discharges patients whose ETA has arrived and returns on-shift doctors to the BST. Input: N/A. Output: N/A.
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
                bst::Node* d_node = new bst::Node(d, d->getSkill());
                shiftDoctors.insert(d_node);
            }
            it = currentPairings.erase(it);
        }
        else
        {
            it++;
        }
    }
}

// Moves doctors whose shift start time has arrived into the on-shift BST. Input: N/A. Output: N/A.
void Simulation::startShifts()
{
    while (!offShiftDoctors.empty() && offShiftDoctors.top()->getStartTime() <= time)
    {
        Doctor *d = offShiftDoctors.top();
        offShiftDoctors.pop();
        if (isOnShift(d))
        {
            bst::Node* d_node = new bst::Node(d, d->getSkill());
            shiftDoctors.insert(d_node);
        }
    }
}

// Pairs arrived waiting patients with highest-skill available doctors and marks timeouts. Input: N/A. Output: N/A.
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
        bst::Node* to_remove = shiftDoctors.find(d->getID(), d->getSkill());
        shiftDoctors.remove(to_remove);
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

// Checks whether a doctor is currently within shift hours. Input: Doctor pointer d. Output: true if on shift.
bool Simulation::isOnShift(Doctor *d)
{
    return d->getStartTime() <= time && time < d->getEndTime();
}

// Computes treatment duration from patient condition and doctor skill. Input: Patient* p, Doctor* d. Output: minutes >= 1.
int Simulation::treatmentTime(Patient *p, Doctor *d)
{
    return std::max(1, 10 + p->getCondition() - d->getSkill());
}

// Looks up a Patient in BTree records by identity fields. Input: name, age, birthdate. Output: Patient* or nullptr.
Patient *Simulation::findPatient(const std::string &name, int age, const std::string &birthdate)
{
    Person probe(name, age, birthdate);
    return dynamic_cast<Patient *>(records.search(probe.getID()));
}

// Looks up a Doctor in BTree records by identity fields. Input: name, age, birthdate. Output: Doctor* or nullptr.
Doctor *Simulation::findDoctor(const std::string &name, int age, const std::string &birthdate)
{
    Person probe(name, age, birthdate);
    return dynamic_cast<Doctor *>(records.search(probe.getID()));
}

// Returns the current simulation time in minutes. Input: N/A. Output: time integer.
int Simulation::getTime() { return time; }
// Returns whether pairing has run for the current minute. Input: N/A. Output: paired boolean.
bool Simulation::isPaired() { return paired; }

// Returns arrived waiting patients sorted by priority. Input: N/A. Output: vector of Patient pointers.
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

// Returns all doctors stored in BTree records. Input: N/A. Output: vector of Doctor pointers.
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

// Counts patients scheduled to arrive after the current minute. Input: N/A. Output: count integer.
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

// Returns the patient currently paired with doctor d. Input: Doctor pointer d. Output: Patient* or nullptr.
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

// Returns active doctor-patient pairings. Input: N/A. Output: const reference to pairings vector.
const std::vector<std::pair<Doctor *, Patient *>> &Simulation::getPairings() { return currentPairings; }
// Returns discharged patients. Input: N/A. Output: const reference to discharged vector.
const std::vector<Patient *> &Simulation::getDischarged() { return discharged; }
// Returns patients who failed to be treated in time. Input: N/A. Output: const reference to failed vector.
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