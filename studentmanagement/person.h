#pragma once
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Person {
private:
    int age;
    string name;

public:
    Person() = default;

    Person(string personName, int personAge) : name(personName), age(personAge) {}

    void setName(string personName) {
        this->name = personName;
    }

    string getName() const {
       return name;
    }

    void setAge(int personAge) {
        this->age = personAge;
    }

    int getAge() const {
        return age;
    }

    virtual void displayPerson() const = 0;
    //virtual void displayPerson() const = 0;
    virtual void readDataFromStream(istream& is) = 0;

    virtual void writeDataToStream(ostream& os) const  {
        os << age << " " << name;
    }

    virtual int getId() const = 0;
    virtual string getType() const = 0;
    virtual void updatePerson() = 0; // New virtual function for updating a person
    virtual ~Person() = default;
};

