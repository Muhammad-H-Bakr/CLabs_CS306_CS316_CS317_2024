#include <bits/stdc++.h> // important.

using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(0.0, 100.0);
    vector<int> vec;
    for (int i = 0; i < 100; i++) {
        vec.push_back((int) dist(gen));
    }
    sort(vec.begin(), vec.end());
    for (int i: vec) {
        cout << i << endl;
    }
    fstream file("D:\\FilesLab\\tester.dat", ios::in | ios::out | ios::binary);
    for (int &i: vec) {
        file.write(reinterpret_cast<const char *>(&i),
                   sizeof(&i));
    }
    file.close();
    return 0;
}
