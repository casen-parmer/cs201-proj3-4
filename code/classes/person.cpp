// header comment

#include "person.h"

#include <functional>

Person::Person(std::string name, int age, std::string birthdate)
    : name(name), age(age), birthdate(birthdate),
      id(std::hash<std::string>{}(name + "|" + std::to_string(age) + "|" + birthdate)) {}

std::string Person::getName() { return name; }
int Person::getAge() { return age; }
std::string Person::getBirthdate() { return birthdate; }
std::size_t Person::getID() { return id; }