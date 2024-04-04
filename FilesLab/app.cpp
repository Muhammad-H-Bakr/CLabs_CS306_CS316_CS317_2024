#include "person.h"

int main() {
    fstream file("D:\\FilesLab\\persons_data.dat",
                 ios::in | ios::out | ios::binary); //Change File path as pleased.
    set<int> keys; //For uniqueness purposes.
    for (int i = 0; i < 1000; i++) {
        keys.insert(i); //Recent Keys.
        Person p("", "", i, 18); //No names, id incremented from 0 to 999, and 18 yrs default.
        file.write(reinterpret_cast<char *>(&p),
                   sizeof(p));
    }
    int querySelector = -1;
    while (querySelector != 0) { //Start Query Session.
        file.seekg(0); //Cursor points to the beginning of the file.
        cout << "Enter your Query:\n0. Close the program.\n" <<
             "1. Insert Object into the Offset Identified by ID.\n" <<
             "2. Get Object from the Index Identified by ID.\n";
        cin >> querySelector;
        if (querySelector == 0) { // Query 0.
            break;
        } else if (querySelector == 1) {
            int id, index = -1;
            cout << "Enter the ID:\n";
            cin >> id;
            Person p;
            for (int i = 0; i < 1000; i++) { // Query 1.
                file.read(reinterpret_cast<char *>(&p),
                          sizeof(p));
                if (p.getId() == id) {
                    index = i;
                    break;
                }
            }
            if (index == -1) { //ID is NOT in the file.
                cout << "Unavailable ID\n";
            } else {
                string str;
                int num;
                cout << "Enter last name new value:" << endl;
                cin >> str;
                p.setLastName(str);
                cout << "Enter first name new value:" << endl;
                cin >> str;
                p.setFirstName(str);
                cout << "Enter ID new value:" << endl;
                cin >> num;
                keys.erase(p.getId()); //Delete recent ID.
                while (keys.contains(num)) { //Check Uniqueness.
                    cout << "Another person have this ID, Try a different one." << endl;
                    cin >> num;
                }
                p.setId(num);
                cout << "Enter Age new value:" << endl;
                cin >> num;
                p.setAge(num);
                file.seekg(index * sizeof(Person)); // NOLINT(*-narrowing-conversions)
                file.write(reinterpret_cast<char *>(&p),
                           sizeof(p));
            }
        } else if (querySelector == 2) { //Query 2.
            int id, index = -1;
            cout << "Enter the ID:\n";
            cin >> id;
            Person p;
            for (int i = 0; i < 1000; i++) {
                file.read(reinterpret_cast<char *>(&p),
                          sizeof(p));
                if (p.getId() == id) {
                    index = i;
                    break;
                }
            }
            if (index == -1) {
                cout << "Unavailable ID\n";
            } else {
                p.Info();
            }
        } else { //Invalid Query Selection.
            cout << "Invalid Input!" << endl;
        }
    }
    file.close();
    return 0;
}