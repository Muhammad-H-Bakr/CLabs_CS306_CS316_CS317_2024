#include "tester.h"

int main(){
    auto start = high_resolution_clock::now();
    double area = trapQuad(0, 10); //integration from 0 to 10 for f(x) = x^2 using N = 100;
    cout << "Area: " << area << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << "Time for trap algorithm: " << duration.count() << "ns" << endl;
}