#include "Quiz1.h"

//Use Functions and Classes here.

int main() {
    string name;
    int price;
    cout << "Enter Book's Name:";
    cin >> name;
    cout << "Enter Book's Price:";
    cin >> price;
    Book book(name,price);
    book.validate();
}