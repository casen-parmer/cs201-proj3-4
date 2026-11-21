/*
Shelbe Yousey, Casen Parmer, Riley Herchert - Dr. Don Yessick - Lucas Hasting
Declares random patient/doctor generation and loading helpers for Simulation.
*/

#pragma once

#include "simulation.h"

namespace dataController
{
    void loadData(Simulation &sim, int numPatients, int numDoctors, bool enableTestHarness);
    Patient generatePatient();
    Doctor generateDoctor();
}