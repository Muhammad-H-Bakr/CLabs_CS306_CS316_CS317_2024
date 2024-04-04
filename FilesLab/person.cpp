#include "person.h"

#include <utility>

Person::Person() {
    validate();
}

Person::Person(string Lname, string Fname, int IdNum, int AgeNum) {
    last_name = std::move(Lname);
    first_name = std::move(Fname);
    id = IdNum;
    age = AgeNum;
    validate();
}

int Person::getId() const {
    return id;
}

int Person::getAge() const {
    return age;
}

string Person::getFirstName() const {
    return first_name;
}

string Person::getLastName() const {
    return last_name;
}

void Person::setAge(int AgeNum) {
    age = AgeNum;
    validate();
}

void Person::setId(int IdNum) {
    id = IdNum;
    validate();
}

void Person::setFirstName(string Fname) {
    first_name = std::move(Fname);
    validate();
}

void Person::setLastName(string Lname) {
    last_name = std::move(Lname);
    validate();
}

void Person::validate() {
    if (id < 0) {
        id = 0;
    }
    if (age < 18) { //Own Preference.
        age = 18;
    }
    first_name = first_name.substr(0, 15);
    last_name = last_name.substr(0, 15);
}

void Person::Info() const {
    cout << "Last Name: " << getLastName() << ", First Name: "
         << getFirstName() << ", Id: " << getId() << ", Age: " << getAge() << "." << endl;
}