#include "home.h"
#include "smartlight.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    
    home runningHome;
    int choice;

    cout << "welcome user, what would you like to do?" << endl;
    cout << "1. create new home" << endl;
    cout << "2. load existing home from file" << endl;
    cout << "0. exit" << endl;

    cin >> choice;
    cin.ignore(); // clear newline

    if (choice == 1) {
        cout << "Enter owner name: ";
        string name;
        getline(cin, name);
        runningHome = home(name);
    }
    else if (choice == 2) {
        cout << "Enter filename to load: ";
        string filename;
        getline(cin, filename);
        runningHome.loadFromFile(filename);
    }
    else if (choice == 0) {
        cout << "goodbye" << endl;
        return 0;
    }

    // Home menu loop
    do {
        cout << "\nwhat would you like to do in your home?" << endl;
        cout << "1. getOwnerName" << endl;
        cout << "2. getNumDevices" << endl;
        cout << "3. setOwnerName" << endl;
        cout << "4. addDevice" << endl;
        cout << "5. removeDevice" << endl;
        cout << "6. seeAllDevices" << endl;
        cout << "7. turn on or off device" << endl;
        cout << "8. change brightness of a smartlight" << endl;
        cout << "9. save home to file" << endl;
        cout << "0. exit" << endl;

        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Owner: " << runningHome.getOwnerName() << endl;
        }
        else if (choice == 2) {
            cout << "Number of devices: " << runningHome.getNumDevices() << endl;
        }
        else if (choice == 3) {
            cout << "Enter new owner name: ";
            string newName;
            getline(cin, newName);
            runningHome.setOwnerName(newName);
        }
        else if (choice == 4) {
            cout << "Enter device type (D=device, S=smartlight): ";
            char type;
            cin >> type;
            cin.ignore();

            if (type == 'D') {
                int id;
                string name, location;
                cout << "Enter id: "; cin >> id; cin.ignore();
                cout << "Enter name: "; getline(cin, name);
                cout << "Enter location: "; getline(cin, location);
                device d(id, name, location);
                runningHome.addDevice(d);
            }
            else if (type == 'S') {
                int brightness, id;
                string name, location;
                cout << "Enter brightness: "; cin >> brightness; cin.ignore();
                cout << "Enter id: "; cin >> id; cin.ignore();
                cout << "Enter name: "; getline(cin, name);
                cout << "Enter location: "; getline(cin, location);
                smartlight sl(id, name, location, brightness);
                runningHome.addDevice(sl);
            }
        }
        else if (choice == 5) {
            int id;
            cout << "Enter device ID to remove: ";
            cin >> id;
            runningHome.removeDevice(id);
        }
        else if (choice == 6) {
            runningHome.printDevices();
        }
        else if (choice == 7) {
            int id;
            cout << "Enter device ID: ";
            cin >> id;

            int onChoice;
            cout << "Enter 1 to turn ON, 0 to turn OFF: ";
            cin >> onChoice;

            runningHome.toggleDevice(id, onChoice == 1);
        }
        else if (choice == 8) {
            int id, brightness;
            cout << "Enter device ID: ";
            cin >> id;
            cout << "Enter new brightness: ";
            cin >> brightness;
            runningHome.changeBrightness(id, brightness);
        }
        else if (choice == 9) {
            std::cout << "Enter filename to save (e.g. home.txt): ";
            std::string filename;
            std::cin >> filename;
            runningHome.save(filename);
        }


    } while (choice != 0);

    cout << "goodbye" << endl;
    
    
    return 0;
}