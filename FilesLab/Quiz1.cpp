#include "Quiz1.h"

Book::Book(const string &nm, double pr) {
    setName(nm);
    setPrice(pr);
}

void Book::setPrice(double pr) {
    price = pr;
}

void Book::setName(const string &nm) {
    name = nm;
}

void Book::validate() {
    cout << "Call to print before validate: " << endl;
    printInfo();
    if (name.length() > 10) {
        name = name.substr(0, 10);
    }
    if (price < 0) {
        price = 0;
    }
    cout << "Call to print after validate: " << endl;
    printInfo();
}

string Book::getName() const {
    return name;
}

double Book::getPrice() const {
    return price;
}

void Book::printInfo() const {
    cout << "name of Book: " << getName() << endl << "price: " << getPrice() << endl;
}