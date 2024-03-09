#ifndef CPPTRIAL_TESTER_H
#define CPPTRIAL_TESTER_H

#include <bits/stdc++.h> // important.

using namespace std;
//Declare Functions and Portfolio of Classes here.


class GradeBook {
public:
    explicit GradeBook(string);

    void setCourseName(string);

    [[nodiscard]] string getCourseName() const;

    void displayMessage() const;

private:
    string courseName;
};

#endif //CPPTRIAL_TESTER_H