#pragma once
#include "person.h"
class Teacher : public Person {
private:
    int employeeId;
    string teachingSubject;

public:
    Teacher() = default;

    Teacher(int empId, string empName, int empAge, string empTeachingSubject)
        : Person(empName, empAge), employeeId(empId), teachingSubject(empTeachingSubject) {}

    void setEmployeeId(int empId) {
        employeeId = empId;
    }

    int getEmployeeId() const {
        return employeeId;
    }

    void setTeachingSubject(string subject) {
        teachingSubject = subject;
    }

    string getTeachingSubject() const {
        return teachingSubject;
    }

    void displayPerson() const override {
        /*string name = Person::getName();
        int age = Person::getAge();*/
        std::cout << "Employee ID: " << employeeId << std::endl;
        std::cout << "Name:  " << getName() << std::endl;
        std::cout << "Age: " << getAge() << std::endl;
        std::cout << "Teaching Subject: " << teachingSubject << std::endl;
    }

    void readDataFromStream(istream& is) override {
        string name = Person::getName();
        int age = Person::getAge();
        is >> employeeId >> name >> age >> teachingSubject;
    }

    void writeDataToStream(ostream& os) const override {
        string name = Person::getName();
        int age = Person::getAge();
        os << "T " << employeeId << " " << name << " " << age << " " << teachingSubject;
    }

    int getId() const override {
        return employeeId;
    }

    string getType() const override {
        return "Teacher";
    }

    void updatePerson() override {
        // Implement update for Teacher if needed
    }
};