#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <string>
#include <vector>
#include <memory>
using namespace std;

#include "person.h"
#include "Teacher.h"
#include "staff.h"
#include "student.h"

class PeopleHandler {
private:
    vector<unique_ptr<Person>> people;

    void writeToTextFile(const string& filename) {
        ofstream outFile(filename);

        if (!outFile.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        for (const auto& person : people) {
            person->writeDataToStream(outFile);
            outFile << endl;
        }

        outFile.close();
    }

    void readFromTextFile(const string& filename) {
        ifstream inFile(filename);

        if (!inFile.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        people.clear();

        while (inFile) {
            char personType;
            int rollNo;
            string name;
            int age;
            string specs;

            while (inFile >> personType >> rollNo >> name >> age >> specs) {
                //unique_ptr<Person> newPerson = nullptr;

                if (personType == 'S') {
                    unique_ptr<Student> newStudent = nullptr;
                    newStudent = make_unique<Student>();
                    newStudent->setName(name);
                    newStudent->setAge(age);
                    newStudent->setRollno(rollNo);
                    newStudent->setStudyField(specs);
                    people.push_back(move(newStudent));
                }
                else if (personType == 'T') {
                    unique_ptr<Teacher> newTeacher = nullptr;
                    newTeacher = make_unique<Teacher>();
                    newTeacher->setName(name);
                    newTeacher->setAge(age);
                    newTeacher->setEmployeeId(rollNo);
                    newTeacher->setTeachingSubject(specs);
                    people.push_back(move(newTeacher));
                }
                else if (personType == 'F') {
                    unique_ptr<Staff> newStaff = nullptr;
                    newStaff = make_unique<Staff>();
                    newStaff->setName(name);
                    newStaff->setAge(age);
                    newStaff->setID(rollNo);
                    newStaff->setRole(specs);
                    people.push_back(move(newStaff));
                }



            }


            /*inFile >> personType;

            if (!inFile) {
                break;
            }

            unique_ptr<Person> newPerson = nullptr;

            if (personType == 'S') {
                newPerson = make_unique<Student>();
            }
            else if (personType == 'T') {
                newPerson = make_unique<Teacher>();
            }
            else if (personType == 'F') {
                newPerson = make_unique<Staff>();
            }

            if (newPerson) {
                newPerson->readDataFromStream(inFile);
                people.push_back(move(newPerson));
            }*/
        }

        inFile.close();
    }

public:
    PeopleHandler() {
        readFromTextFile("people.txt");
    }

    ~PeopleHandler() = default;

    void addNewStudent() {
        int rollno, age;
        string name, studyField;

        while (true) {
            cout << "Enter Rollno      : ";
            if (cin >> rollno) {
                break;
            }
            else {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        for (const auto& person : people) {
            const Student* student = dynamic_cast<const Student*>(person.get());
            if (student && student->getRollno() == rollno) {
                cout << "\t\tStudent Already Exists" << endl;
                return;
            }
        }

        cout << "Enter Name        : ";
        cin.ignore();
        getline(cin, name);

         
        
        while (true) {
            cout << "Enter Age  : ";
            if (cin >> age) {
                break;
            }
            else {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        cout << "Enter Study Field : ";
        cin.ignore();
        getline(cin, studyField);

        auto newStudent = make_unique<Student>(rollno, name, age, studyField);
        people.push_back(move(newStudent));

        writeToTextFile("people.txt");
    }

    void addNewTeacher() {
        int employeeId, age;
        string name, teachingSubject;

        while (true) {
            cout << "Enter Employee ID      : ";
            if (cin >> employeeId) {
                break;
            }
            else {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        for (const auto& person : people) {
            const Teacher* teacher = dynamic_cast<const Teacher*>(person.get());
            if (teacher && teacher->getEmployeeId() == employeeId) {
                cout << "\t\tTeacher Already Exists" << endl;
                return;
            }
        }

        cout << "Enter Name            : ";
        cin.ignore();
        getline(cin, name);

        while (true) {
            cout << "Enter Age     : ";
            if (cin >> age) {
                break;
            }
            else {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        cout << "Enter Teaching Subject : ";
        cin.ignore();
        getline(cin, teachingSubject);

        auto newTeacher = make_unique<Teacher>(employeeId, name, age, teachingSubject);
        people.push_back(move(newTeacher));

        writeToTextFile("people.txt");
    }

    void addNewStaff() {
        int staffId, age;
        string name, role;

        while (true) {
            cout << "Enter Staff ID : ";
            if (cin >> staffId) {
                break;
            }
            else {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        for (const auto& person : people) {
            const Staff* staff = dynamic_cast<const Staff*>(person.get());
            if (staff && staff->getId() == staffId) {
                cout << "\t\tStaff Member Already Exists" << endl;
                return;
            }
        }

        cout << "Enter Name     : ";
        cin.ignore();
        getline(cin, name);

        while (true) {
            cout << "Enter Age    : ";
            if (cin >> age) {
                break;
            }
            else {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        cout << "Enter Role     : ";
        cin.ignore();
        getline(cin, role);

        auto newStaff = make_unique<Staff>(staffId, name, age, role);
        people.push_back(move(newStaff));

        writeToTextFile("people.txt");
    }

    void displayAllPeople() const {
        if (people.empty()) {
            cout << "\t\t No People Found " << endl;
        }


        for (const auto& person : people) {
            person->displayPerson();
            cout << endl;
        }
    }

    void searchPerson() const {
        int id;
        cout << "Enter ID to Search : ";
        cin >> id;

        for (const auto& person : people) {
            if (person->getId() == id) {
                person->displayPerson();
                return;
            }
        }

        cout << "\t\tPerson Not Found" << endl;
    }

    void updatePerson() {
        int id;
        cout << "\t\tEnter ID to Update Record : ";
        cin >> id;

        auto it = find_if(people.begin(), people.end(), [id](const auto& person) {
            return person->getId() == id;
            });

        if (it != people.end()) {
            (*it)->displayPerson();

            cout << "\t\tChoose attribute to update:" << endl;
            cout << "\t\t 1. Name" << endl;
            cout << "\t\t 2. Age" << endl;
            cout << "\t\t 3. Update Specific Details" << endl;
            cout << "\t\tEnter Your Choice : ";

            int choice;
            cin >> choice;

            switch (choice) {
            case 1: {
                string name;
                cout << "\t\tEnter New Name :";
                cin.ignore();
                getline(cin, name);
                (*it)->setName(name);
                break;
            }
            case 2: {
                int age;
                while (true) {
                    cout << "\t\tEnter New Age :";
                    if (cin >> age) {
                        break;
                    }
                    else {
                        cout << "Invalid input. Please enter a number." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                (*it)->setAge(age);
                break;
            }
            case 3: {
                // Dynamically check the type using dynamic_cast
                if (auto student = dynamic_cast<Student*>(it->get())) {
                    string StudyField;
                    cout << "\t\tEnter New program :";
                    cin.ignore();
                    getline(cin, StudyField);
                    student->setStudyField(StudyField);
                }
                else if (auto teacher = dynamic_cast<Teacher*>(it->get())) {
                    string newTeachingSubject;
                    cout << "\t\tEnter New Teaching Subject :";
                    cin.ignore();
                    getline(cin, newTeachingSubject);
                    teacher->setTeachingSubject(newTeachingSubject);
                }
                else if (auto staff = dynamic_cast<Staff*>(it->get())) {
                    string newRole;
                    cout << "\t\tEnter New Role  : ";
                    cin.ignore();
                    getline(cin, newRole);
                    staff->setRole(newRole);
                }
                else {
                    cout << "\t\tInvalid Person Type" << endl;
                }
                break;
            }
            default:
                cout << "\t\tInvalid Number" << endl;
            }

            writeToTextFile("people.txt");
        }
        else {
            cout << "\t\tPerson Not Found" << endl;
        }
    }

    void deletePerson() {
        int id;
        while (true) {
            cout << "\t\tEnter ID to Delete : ";
            if (cin >> id) {
                break;
            }
            else {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        auto it = remove_if(people.begin(), people.end(), [id](const auto& person) {
            return person->getId() == id;
            });

        if (it != people.end()) {
            people.erase(it, people.end());
            cout << "\t\tPerson Removed Successfully" << endl;
            writeToTextFile("people.txt");
        }
        else {
            cout << "\t\tPerson Not Found" << endl;
        }
    }

    int countPeopleOfType(const string& type) const {
        int count = 0;
        for (const auto& person : people) {
            if (person->getType() == type) {
                count++;
            }
        }
        return count;
    }

    int countStudents() const {
        return countPeopleOfType("Student");
    }

    int countTeachers() const {
        return countPeopleOfType("Teacher");
    }

    int countStaff() const {
        return countPeopleOfType("Staff");
    }

    int countTotalPeople() const {
        return people.size();
    }

    void handlePeople() {
        bool choice = true;


        while (choice) {
            int op;

            cout << "\n\t\t--------------------------------";
            cout << "\n\t\t*** School Management System ***";
            cout << "\n\t\t--------------------------------";
            cout << "\n\t\t 1. Add New Student " << endl;
            cout << "\t\t 2. Add New Teacher " << endl;
            cout << "\t\t 3. Add New Staff " << endl;
            cout << "\t\t 4. Display All People " << endl;
            cout << "\t\t 5. Search Person " << endl;
            cout << "\t\t 6. Update Person " << endl;
            cout << "\t\t 7. Delete Person " << endl;
            cout << "\t\t 8. Count Students " << endl;
            cout << "\t\t 9. Count Teachers " << endl;
            cout << "\t\t 10. Count Staff " << endl;
            cout << "\t\t 11. Count Total People " << endl;
            cout << "\t\t 12. Exit " << endl;
            cout << "\t\t Enter Your Choice : ";

            cin >> op;

            if (cin.fail()) {
                cout << "\t\tInvalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (op) {
            case 1:
                addNewStudent();
                break;
            case 2:
                addNewTeacher();
                break;
            case 3:
                addNewStaff();
                break;
            case 4:
                displayAllPeople();
                break;
            case 5:
                searchPerson();
                break;
            case 6:
                updatePerson();
                break;
            case 7:
                deletePerson();
                break;
            case 8:
                cout << "\t\tTotal Students: " << countStudents() << endl;
                break;
            case 9:
                cout << "\t\tTotal Teachers: " << countTeachers() << endl;
                break;
            case 10:
                cout << "\t\tTotal Staff: " << countStaff() << endl;
                break;
            case 11:
                cout << "\t\tTotal People in the school system: " << countTotalPeople() << endl;
                break;
            case 12:
                
                choice = false;
                break;
            default:
                cout << "\t\tInvalid Choice. Please enter a valid option.\n";
            }

            /*cout << "\t\tDo You Want to Continue [(y) for Yes/ and any other (key) for No] ? : ";
            cin >> choice;*/

        } 
    }
};
