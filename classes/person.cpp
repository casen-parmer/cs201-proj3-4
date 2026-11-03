// header comment

#ifndef PERSON_CPP
#define PERSON_CPP

#include "person.h"

Person::Person(std::string name, int age, std::string birthdate) : name(name), age(age), birthdate(birthdate) {}
std::string Person::getName() { return name; }
int Person::getAge() { return age; }
std::string Person::getBirthdate() { return birthdate; }

#endif
