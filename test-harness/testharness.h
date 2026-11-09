// header comment

#ifndef TESTHARNESS_H
#define TESTHARNESS_H

#include <string>

void runAllTests();
void printTestResult(bool success, std::string name, std::string desc);

#endif