#include <bits/stdc++.h>

using namespace std;

int main() {
    int deleted = 'x'/*120*/, delimiter = '|'/*124*/,
            queryHandler; //Delete symbol, delimiter and querying.
    fstream file("VarLength.dat", ios::in | ios::out | ios::binary);
    if (!file.is_open()) { //File did NOT open.
        cerr << "Unable to open the file";
        exit(-1);
    }
    while (true) {
        cout << "Enter a query number: \n0. Close program.\n1. Put a new set at end of file.\n2."
                " Delete a set with given index.\n";
        cin >> queryHandler;
        if (queryHandler == 0) {
            break;
        } else if (queryHandler == 1) {
            file.close();
            file.open("D:\\FilesLab\\VarLength.dat", ios::binary | ios::app);
            int size;
            cout << "Enter the size of the set:\n";
            cin >> size;
            while (size <= 0) { //Validate.
                cout << "Invalid Size! Enter a positive number for the size:\n";
                cin >> size;
            }
            int vec[size];
            cout << "Enter the elements: \n";
            for (int i = 0; i < size; i++) {
                cin >> vec[i];
            }
            file.write(reinterpret_cast<char *>(&vec),
                       size * sizeof(int)); // NOLINT(*-narrowing-conversions)
            file.write(reinterpret_cast<char *>(&delimiter), sizeof(int));
            file.close();
            file.open("D:\\FilesLab\\VarLength.dat", ios::in | ios::out | ios::binary);
        } else if (queryHandler == 2) {
            file.seekg(0); //Move to beginning of file.
            int index, counter = 0;
            cout << "Enter the index of the set:\n";
            cin >> index;
            while (index < 0) { //Validate.
                cout << "Invalid Index! Enter a positive number for the index:\n";
                cin >> index;
            }
            int isDelimiter;
            while (!file.eof()) {
                if (counter == index) {
                    break;
                }
                file.read(reinterpret_cast<char *>(&isDelimiter), sizeof(int));
                if (isDelimiter == delimiter) {
                    counter++;
                }
            }
            if (counter < index) { //Didn't Find the index.
                cout << "Index out of range.\n";
            } else if (counter == index) { //Found the index.
                //Replace the first element with 'x' to indicate set deletion.
                file.write(reinterpret_cast<char *>(&deleted), sizeof(int));
            }
        } else {
            cout << "Invalid Selection!" << endl;
        }
    }
    file.close();
    return 0;
}