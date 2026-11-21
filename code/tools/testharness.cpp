/*
Shelbe Yousey, Casen Parmer, Riley Herchert - Dr. Don Yessick - Lucas Hasting
Runs headless simulation tests with expected inputs and outputs.
*/

#include "testharness.h"
#include "simulation.h"
#include <iostream>

static bool g_failed = false;

// Prints one test result and tracks failure state. Input: success flag, name, description. Output: N/A.
void printTestResult(bool success, std::string name, std::string desc)
{
    if (!success)
        g_failed = true;
    std::cout << (success ? "[PASS] " : "[FAIL] ") << name << ": " << desc << '\n';
}

// Runs expected-input/output checks on Simulation. Input: N/A. Output: N/A.
void runAllTests()
{

    g_failed = false;
    Simulation sim(480);
    sim.addPerson(Doctor("Dr. Low", 40, "1985-01-01", 4, true, 480, 500));
    sim.addPerson(Doctor("Dr. High", 45, "1980-01-01", 9, true, 480, 500));
    sim.addPerson(Patient("Low", 31, "1994-01-01", 3, 480));
    sim.addPerson(Patient("High", 30, "1995-01-01", 5, 480));
    sim.addPerson(Patient("Late", 25, "2000-01-01", 6, 500));

    sim.step();
    Doctor *dHigh = sim.findDoctor("Dr. High", 45, "1980-01-01");
    Patient *pHigh = sim.findPatient("High", 30, "1995-01-01");
    printTestResult(dHigh && pHigh && sim.getPairings().size() == 2 && sim.patientOf(dHigh) == pHigh && pHigh->getETA() == 486,
                    "Pairing", "Highest-skill doctor takes higher-condition patient with ETA 486");

    for (int i = 0; i < 9; i++)
        sim.step();
    printTestResult(sim.getDischarged().size() == 2 && sim.getPairings().empty(),
                    "Discharge", "Both paired patients discharge by minute 489");

    for (int i = 0; i < 42; i++)
        sim.step();
    Patient *pLate = sim.findPatient("Late", 25, "2000-01-01");
    printTestResult(pLate && sim.getFailed().size() == 1 && pLate->getStatus() == PatientStatus::FAILED_TO_TREAT,
                    "Timeout", "Unpaired patient fails after exceeding 30-minute wait limit");
}

#ifdef TEST_MAIN
// Test entry point. Input: N/A. Output: 0 if all pass, 1 otherwise.
int main()
{
    runAllTests();
    return g_failed ? 1 : 0;
}
#endif
