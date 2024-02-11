#pragma once
#include "person.h"
class Student : public Person {
private:
    int rollno;
    string studyField;

public:
    Student() = default;

    Student(int stdId, string stdName, int stdAge, string stdStudyField)
        : Person(stdName, stdAge), rollno(stdId), studyField(stdStudyField) {}

    void setRollno(int stdId) {
        rollno = stdId;
    }

    int getRollno() const {
        return rollno;
    }

    void setStudyField(string field) {
        studyField = field;
    }

    string getStudyField() const {
        return studyField;
    }

    void displayPerson() const override {
        /*string name = Person::getName();
        int age = Person::getAge();*/
        std::cout << "Roll No: " << rollno << std::endl;
        std::cout << "Name: " << getName() << std::endl;
        std::cout << "Age: " << getAge() << std::endl;
        std::cout << "Study Field: " << studyField << std::endl;
    }

    void readDataFromStream(istream& is) override {
        string name = Person::getName();
        int age = Person::getAge();
        is >> rollno >> name >> age >> studyField;
    }

    void writeDataToStream(ostream& os) const override {
        string name = Person::getName();
        int age = Person::getAge();
        os << "S " << rollno << " " << getName() << " " << getAge() << " " << studyField;
    }

    int getId() const override {
        return rollno;
    }

    string getType() const override {
        return "Student";
    }

    void updatePerson() override {
        // Implement update for Student if needed
    }
};