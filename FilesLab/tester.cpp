#include "tester.h"

#include <utility>

//Define Functions and Constructors here.

GradeBook::GradeBook(string name) {
    setCourseName(std::move(name));
}

void GradeBook::setCourseName(string name) {
    if (name.size() < 25) {
        courseName = std::move(name);
    } else {
        courseName = name.substr(0, 25);
        cerr << "Name\"" << name << "\" exceeds maximum length(25)." << endl
             << "Limiting courseName to the first 25 characters." << endl;
    }
}

string GradeBook::getCourseName() const {
    return courseName;
}

void GradeBook::displayMessage() const {
    cout << "Welcome to the grade book for" << getCourseName() << "!" << endl;
}