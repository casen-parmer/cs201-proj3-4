// header comment

#pragma once

#include <string>

class Person
{
protected:
    std::string name;
    int age;
    std::string birthdate;
    int id; // derived directly from combination of name and birthdate
public:
    Person(std::string name, int age, std::string birthdate);
    std::string getName();
    int getAge();
    std::string getBirthdate();
    std::size_t getID();
};