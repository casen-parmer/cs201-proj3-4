/*
Shelbe Yousey, Casen Parmer, Riley Herchert - Dr. Don Yessick - Lucas Hasting
Declares the Simulation class managing hospital queues, pairings, and time steps.
*/

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
    b_tree::BTree records{10};
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
    void fireDoctor(Doctor *d);
    std::vector<Patient *> getWaiting();
    std::vector<Doctor *> getDoctors();
    int getUpcomingCount();
    Patient *patientOf(Doctor *d);
    const std::vector<std::pair<Doctor *, Patient *>> &getPairings();
    const std::vector<Patient *> &getDischarged();
    const std::vector<Patient *> &getFailed();
};