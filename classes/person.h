// header comment

#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person
{
protected:
    static int next_id;
    std::string name;
    int age;
    std::string birthdate;
    int id;

public:
    Person(std::string name, int age, std::string birthdate) {
        this->name = name;
        this->age = age;
        this->birthdate = birthdate;
        this->id = next_id++;
    }
    std::string getName() {
        return name;
    }
    int getAge() {
        return age;
    }
    std::string getBirthdate() {
        return birthdate;
    }
    int getId() {
        return id;
    }
};

int Person::next_id = 1;

#endif
