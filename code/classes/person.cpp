/*
Shelbe Yousey, Casen Parmer, Riley Herchert - Dr. Don Yessick - Lucas Hasting
Implements the Person class constructors, getters, and hash-based ID.
*/

#include "person.h"

#include <functional>

// Constructs a Person and computes a hashed ID. Input: name, age, birthdate. Output: N/A.
Person::Person(std::string name, int age, std::string birthdate)
    : name(name), age(age), birthdate(birthdate),
      id(std::hash<std::string>{}(name + "|" + std::to_string(age) + "|" + birthdate)) {}

// Returns the person's name. Input: N/A. Output: name string.
std::string Person::getName() { return name; }
// Returns the person's age. Input: N/A. Output: age in years.
int Person::getAge() { return age; }
// Returns the person's birthdate. Input: N/A. Output: birthdate string.
std::string Person::getBirthdate() { return birthdate; }
// Returns the person's unique ID. Input: N/A. Output: hashed ID value.
std::size_t Person::getID() { return id; }