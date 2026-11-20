// header comment

#pragma once

#include <string>
#include <vector>
#include "bst.h"
#include "btree.h"
#include "maxheap.h"
#include "patient.h"
#include "doctor.h"
#include "keys.h"

class Simulation
{
private:
    // constants
    static constexpr int TIME_LIMIT = 30; // minutes a patient is allowed to wait

    // data structures
    // source of truth, owns every patient and doctor
    bTree::bTree<Person, PersonByID> records{10};
    // patients not yet seen, earliest arrival on top
    maxHeap::maxHeap<Patient, PatientByArrival> patientQueue;
    // free doctors on shift, most skilled = max
    bst::Tree shiftDoctors;
    // doctors not yet on shift, earliest start on top
    maxHeap::maxHeap<Doctor, DoctorByStartTime> offShiftDoctors;
    // visits in progress
    std::vector<std::pair<Doctor *, Patient *>> currentPairings;
    std::vector<Patient *> discharged;
    std::vector<Patient *> failed;

    // variables
    int time;
    bool paired;

    // functions
    void dischargePatients();
    void startShifts();
    void createPairings();
    int treatmentTime(Patient *p, Doctor *d);

public:
    // constructor
    Simulation();
    Simulation(int startTime);

    // full minute (both phases)
    void step();
    // half minute for the GUI
    void stepPhase();

    void addPerson(Patient patient);
    void addPerson(Doctor doctor);

    Patient *findPatient(const std::string &name, int age, const std::string &birthdate);
    Doctor *findDoctor(const std::string &name, int age, const std::string &birthdate);

    int getTime();
    bool isPaired();
    bool isOnShift(Doctor *d);
    std::vector<Patient *> getWaiting();
    std::vector<Doctor *> getDoctors();
    int getUpcomingCount();
    Patient *patientOf(Doctor *d);
    const std::vector<std::pair<Doctor *, Patient *>> &getPairings();
    const std::vector<Patient *> &getDischarged();
    const std::vector<Patient *> &getFailed();
};

/*
public:
std::vector<Patient> patients;
std::vector<Doctor> doctors;
b_tree::BTree<Person, int> records{10};
int time;
bool paired = true;

Simulation(std::vector<Patient> patients, std::vector<Doctor> doctors, int start = 480);
Simulation(const Simulation &) = delete;
Simulation &operator=(const Simulation &) = delete;

void step();
// Alternates between start-of-minute and end of minute to make the arrival/pairing clear
void step_phase();

private:
bst::Tree doctor_tree;
void update_arrivals();
void pair_and_close();
};

*/

/*
If we drop the doctor skill >= patient condition requirement, then we can do:
LLRB of doctors on shift sorted by skill -> prefer high skill doctors
Max heap of doctors off shift sorted by start time
Max heap of patients sorted by arrival time
Vector or min heap of current doctor patient pairings
Vectors for discharged and failed patients
B-tree for records

then it’s just for every step:
1. Discharge patient and re-add doctors to LLRB, if completed
2. Add off-shift doctors to LLRB until time > start time
3. Create pairings of doctors and patients, checking that a doctor is still on shift and a patient has not passed their min time to treatment -> if either fails, move patient/doctor to corresponding data structure. Keep iterating until time > arrival time
This way we’re not rebuilding the max heaps at all, we just keep pulling things off the top until time > condition. Then it’s just an additional check for the additional doctor specific or patient specific condition*/