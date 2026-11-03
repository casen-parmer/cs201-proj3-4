// header comment

#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person
{
protected:
    std::string name;
    int age;
    std::string birthdate;

public:
    Person(std::string name, int age, std::string birthdate);
    std::string getName();
    int getAge();
    std::string getBirthdate();
};

#include "person.cpp"

#endif
