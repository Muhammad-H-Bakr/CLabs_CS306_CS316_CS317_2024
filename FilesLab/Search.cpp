#include <bits/stdc++.h> // important.

using namespace std;

int LinSearch(fstream &, int);

int BinSearch(fstream &, int);

int main() {
    fstream file("D:\\FilesLab\\tester.dat", ios::in | ios::out | ios::binary);
    cout << "Index using Linear Search: " << LinSearch(file, 11) << endl;
    cout << "Index using Binary Search: " << BinSearch(file, 11) << endl;
    file.close();
    return 0;
}

int LinSearch(fstream &file, int y) {
    int x, index = -1;
    for (int i = 0; i < 100; i++) {
        file.read(reinterpret_cast<char *>(&x), sizeof(x));
        if (y == x) {
            index = i;
            break;
        }
    }
    return index;
}

int BinSearch(fstream &file, int y) {
    int left = 0, index = -1, mid, value;
    //Get the current end of the file:
    int right = 99;
    while (left <= right) {
        mid = (right + left) / 2;
        //Since This is a binary file We can't seek by offset directly:
        file.seekg(mid * sizeof(int)); // NOLINT(*-narrowing-conversions)
        file.read(reinterpret_cast<char *>(&value), sizeof(int));
        if (value == y) {
            index = mid;
            break;
        } else if (value < y) {
            left = mid + 1; // Move to the right half
        } else {
            right = mid - 1; // Move to the left half
        }
    }
    return index;
}