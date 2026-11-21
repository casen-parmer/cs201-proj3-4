/*
Shelbe Yousey, Casen Parmer, Riley Herchert - Dr. Don Yessick - Lucas Hasting
Declares the unit test runner and result printer for the hospital simulation.
*/

#pragma once

#include <string>

void runAllTests();
void printTestResult(bool success, std::string name, std::string desc);