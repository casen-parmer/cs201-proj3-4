// Hospital event processing, using the existing B-tree, doctor BST and patient priority queue.
#include "simulation.h"
#include "patient_heap.h"
#include <algorithm>
#include <utility>

Simulation::Simulation(std::vector<Patient> patients, std::vector<Doctor> doctors, int start)
    : patients(std::move(patients)), doctors(std::move(doctors)), time(start) {
    for (Patient& p : this->patients) {
        records.insert(&p, p.getId());
    }
    for (Doctor& d : this->doctors) {
        records.insert(&d, d.getId());
        doctor_tree.insert(new bst::Node(&d, d.skill));
    }
    update_arrivals();
    pair_and_close();
}

void Simulation::step() {
    ++time;
    update_arrivals();
    pair_and_close();
    paired = true;
}

void Simulation::step_phase() {
    if (paired) {
        ++time;
        update_arrivals();
        paired = false;
    } else {
        pair_and_close();
        paired = true;
    }
}

void Simulation::update_arrivals() {
    for (Doctor& d : doctors) {
        if (d.patient && d.patient->eta.value() <= time) {
            d.patient->condition = 0;
            d.patient->status = PatientStatus::DISCHARGED;
            d.patient->eta.reset();
            d.patient = nullptr;
        }
       // Doctors will stay after their shift to finish treating a paitent
        d.available = !d.patient && d.start_time <= time && time < d.end_time;
    }

    for (Patient& p : patients) {
        if (p.status == PatientStatus::SCHEDULED && p.arrival_time <= time)
            p.status = PatientStatus::WAITING;
        else if (p.status == PatientStatus::WAITING && time > p.arrival_time && p.condition < 10)
            ++p.condition;
    }
}

void Simulation::pair_and_close() {
    PatientHeap waiting;
    for (Patient& p : patients)
        if (p.status == PatientStatus::WAITING) waiting.push(&p);

    while (!waiting.empty()) {
        Patient* p = waiting.top();
        waiting.pop();
        auto* node = doctor_tree.find_lowest_available_doctor(p->condition, time);
        if (!node) continue; // Skip if no doctor has high enough skill 
        Doctor& d = *node->value;
        d.patient = p;
        d.available = false;
        p->status = PatientStatus::IN_VISIT;
        p->eta = time + std::max(1, 10 + p->condition - d.skill);
    }
    
    for (Patient& p : patients)
        if (p.status == PatientStatus::WAITING && p.condition == 10)
            p.status = PatientStatus::FAILED_TO_TREAT;
}
