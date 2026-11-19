// Discrete hospital simulation; all times are absolute minutes, shifts are [start, end).
#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "bst.h"
#include "btree.h"

class Simulation
{
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

#endif
