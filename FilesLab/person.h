#ifndef CPPTRIAL_PERSON_H
#define CPPTRIAL_PERSON_H

#include <bits/stdc++.h> // important.

using namespace std;

class Person {
private:
    string last_name, first_name;
    int age{}, id{};
public:
    explicit Person();

    explicit Person(string, string, int, int);

    void setLastName(string);

    void setFirstName(string);

    void setId(int);

    void setAge(int);

    [[nodiscard]] string getLastName() const;

    [[nodiscard]] string getFirstName() const;

    [[nodiscard]] int getId() const;

    [[nodiscard]] int getAge() const;

    void validate();

    void Info() const;
};


#endif //CPPTRIAL_PERSON_H
