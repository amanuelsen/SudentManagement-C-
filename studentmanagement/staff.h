#pragma once
#include "person.h"
class Staff : public Person {
private:
    int staffId;
    string role;

public:
    Staff() = default;

    Staff(int sId, string sName, int sAge, string sRole)
        : Person(sName, sAge), staffId(sId), role(sRole) {}

    void displayPerson() const override {
        std::cout << "Staff ID: " << staffId << std::endl;
        std::cout << "Name: " << getName() << std::endl;
        std::cout << "Age: " << getAge() << std::endl;
        std::cout << "Role: " << role << std::endl;
    }

    void readDataFromStream(istream& is) override {
        string name = Person::getName();
        int age = Person::getAge();
      
        is >> staffId >> name >> age >> role;
    }

    void writeDataToStream(ostream& os) const override {
        string name = Person::getName();
        int age = Person::getAge();
        os << "F " << staffId << " " << name << " " << age << " " << role;
    }

    int getId() const override {
        return staffId;
    }
    void setID(int id) {
        this->staffId = id;

    }

    string getType() const override {
        return "Staff";
    }

    string getRole() const {
        return role;
    }

    void setRole(string& newRole) {
        role = newRole;
    }

    void updatePerson() override {
        cout << "\t\tEnter New Role  : ";
        cin.ignore();
        getline(cin, role);
    }
};