#include <bits/stdc++.h>

using namespace std;

int main() {
    int delimiter = '|'; //The agreed upon delimiter.
    random_device rd; //Randomizer.
    mt19937 gen(rd()); //Seed.
    //Generate Integer Numbers as uniformly distributed between 0 and 100 for elements.
    uniform_int_distribution<int> elements(0, 100);
    //Generate Integer Numbers as uniformly distributed between 5 and 10 for sizes.
    uniform_int_distribution<int> sizes(5, 10);
    //Open file and delete its content to write new content:
    ofstream file("VarLength.dat", ios::trunc | ios::binary);
    for (int i = 0; i < 100; i++) {
        int size = sizes(gen); //Create size for each set.
        int vec[size];
        for (int j = 0; j < size; j++) {
            vec[j] = elements(gen); //Put random elements.
        }
        file.write(reinterpret_cast<char *>(&vec),
                   size * sizeof(int)); // NOLINT(*-narrowing-conversions)
        file.write(reinterpret_cast<char *>(&delimiter),
                   sizeof(int)); //Put the delimiter after each set.
    }
    return 0;
}