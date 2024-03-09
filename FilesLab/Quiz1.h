#ifndef CPPTRIAL_QUIZ1_H
#define CPPTRIAL_QUIZ1_H

#include <bits/stdc++.h> // important.

using namespace std;

class Book {

public:
    explicit Book(const string &, double);

    [[nodiscard]] string getName() const;

    [[nodiscard]] double getPrice() const;

    void setName(const string &);

    void setPrice(double);

    void printInfo() const;

    void validate();

private:
    string name;
    double price{0};
};

#endif //CPPTRIAL_QUIZ1_H