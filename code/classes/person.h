// header comment

#pragma once

#include <string>

/*
Shelbe Yousey, Casen Parmer, Riley Herchert - Dr. Don Yessick - Lucas Hasting

This header file defines the Person Class.
*/

class Person
{
protected:
    std::string name;
    int age;
    std::string birthdate;
    int id; // derived directly from combination of name and birthdate
public:
    Person(std::string name, int age, std::string birthdate);
    virtual ~Person() = default;
    std::string getName();
    int getAge();
    std::string getBirthdate();
    std::size_t getID();
};