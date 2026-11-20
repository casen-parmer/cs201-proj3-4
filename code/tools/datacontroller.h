// header comment

#pragma once

#include "simulation.h"

namespace dataController
{
    void loadData(Simulation &sim, int numPatients, int numDoctors, bool enableTestHarness);
    Patient generatePatient();
    Doctor generateDoctor();
}