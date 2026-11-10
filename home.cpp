#include "home.h"
#include "smartlight.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

home::home() : ownerName(""), numDevices(0) {}

home::home(string _ownerName) : ownerName(_ownerName), numDevices(0) {}

// Copy constructor
home::home(const home& RHS) {
    ownerName = RHS.ownerName;
    numDevices = 0;
    for (device* d : RHS.devices) {
        if (d->getType() == 'S') {
            devices.push_back(new smartlight(*(smartlight*)d));
        } else {
            devices.push_back(new device(*d));
        }
        numDevices++;
    }
}

// Assignment operator
home& home::operator=(const home& RHS) {
    if (this != &RHS) {
        // clean up existing
        for (int i = devices.size() - 1; i >= 0; i--) {
            if (devices.at(i) != nullptr) {
                delete devices.at(i);
                devices.at(i) = nullptr;
            }
            devices.pop_back();
        }
        ownerName = RHS.ownerName;
        numDevices = 0;
        for (device* d : RHS.devices) {
            if (d->getType() == 'S') {
                devices.push_back(new smartlight(*(smartlight*)d));
            } else {
                devices.push_back(new device(*d));
            }
            numDevices++;
        }
    }
    return *this;
}

// Load from file (owner name on first line, then comma-separated device info)
home& home::loadFromFile(string fileName) {
    ifstream inputFile;
    inputFile.open(fileName);
    if (inputFile.is_open()) {
        // clear existing devices
        for (int i = devices.size() - 1; i >= 0; i--) {
            if (devices.at(i) != nullptr) {
                delete devices.at(i);
                devices.at(i) = nullptr;
            }
            devices.pop_back();
        }
        numDevices = 0;

        // first line = owner name
        getline(inputFile, ownerName);

        string line;
        while (!inputFile.eof()) {
            getline(inputFile, line);
            if (line.empty()) continue;

            stringstream parseLine(line);
            string type;
            getline(parseLine, type, ','); // first token = type

            if (type == "device") {
                int id;
                string name, location;
                char comma;

                parseLine >> id >> comma;
                getline(parseLine, name, ',');
                getline(parseLine, location);

                devices.push_back(new device(id, name, location));
            }
            else if (type == "smartlight") {
                int brightness, id;
                string name, location;
                char comma;

                parseLine >> brightness >> comma >> id >> comma;
                getline(parseLine, name, ',');
                getline(parseLine, location);

                devices.push_back(new smartlight(id, name, location, brightness));
            }

            numDevices++;
        }

        inputFile.close();
    }
    else {
        cerr << "Error opening file: " << fileName << endl;
    }

    return *this;
}

//save to home to a file
void home::save(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error: could not open file " << filename << " for writing." << std::endl;
        return;
    }

    // First line: owner name
    outFile << ownerName << std::endl;

    // Write each device depending on its type
    for (auto device : devices) {
        // Smartlight format: smartlight,brightness,id,name,location
        if (auto light = dynamic_cast<smartlight*>(device)) {
            outFile << "smartlight,"
                    << light->getBrightness() << ","
                    << light->getDeviceID() << ","
                    << light->getName() << ","
                    << light->getLocation() << std::endl;
        }
        // Generic fallback for other devices
        else {
            outFile << "device,"
                    << device->getDeviceID() << ","
                    << device->getName() << ","
                    << device->getLocation() << std::endl;
        }
    }

    outFile.close();
    std::cout << "Home data saved to " << filename << std::endl;
}

string home::getOwnerName() { return ownerName; }
void home::setOwnerName(string _ownerName) { ownerName = _ownerName; }
int home::getNumDevices() { return numDevices; }

void home::addDevice(const device& _device) {
    if (_device.getType() == 'S') {
        devices.push_back(new smartlight((const smartlight&)_device));
    } else {
        devices.push_back(new device(_device));
    }
    numDevices++;
}

void home::removeDevice(int deviceID)
{
    // Step 1: find the position of the device
    int pos = -1;
    for (int i = 0; i < numDevices; i++)
    {
        if (devices[i] != nullptr && devices[i]->getDeviceID() == deviceID)
        {
            pos = i;
            break;
        }
    }

    // Step 2: if found, delete and shift
    if (pos != -1)
    {
        delete devices[pos];

        for (int j = pos; j < numDevices - 1; j++)
        {
            devices[j] = devices[j + 1];
        }

        devices[numDevices - 1] = nullptr;
        numDevices--;
    }
    else
    {
        std::cout << "Device with ID " << deviceID << " not found." << std::endl;
    }
}


void home::printDevices() {
    cout << "Owner: " << ownerName << endl;
    cout << "Devices (" << numDevices << "):" << endl;
    cout << "------------------" << endl;
    for (device* d : devices) {
        if (d != nullptr) {
            d->print();
            cout << "------------------" << endl;
        }
    }
}

void home::changeBrightness(int _deviceID, int newBrightness) {
    for (device* d : devices) {
        if (d != nullptr && d->getDeviceID() == _deviceID) {
            // Only smartlight has brightness
            if (d->getType() == 'S') {
                smartlight* sl = dynamic_cast<smartlight*>(d);
                if (sl) {
                    sl->setBrightness(newBrightness);
                    cout << "Smartlight " << _deviceID << " brightness set to " << newBrightness << endl;
                }
            } else {
                cout << "Device " << _deviceID << " is not a smartlight." << endl;
            }
            return;
        }
    }
    cout << "Device with ID " << _deviceID << " not found." << endl;
}

void home::toggleDevice(int _deviceID, bool turnOn) {
    for (device* d : devices) {
        if (d != nullptr && d->getDeviceID() == _deviceID) {
            d->setIsOn(turnOn);  // call the device’s setter
            cout << "Device " << _deviceID 
                 << (turnOn ? " turned ON." : " turned OFF.") 
                 << endl;
            return;
        }
    }
    cout << "Device with ID " << _deviceID << " not found." << endl;
}



// Destructor
home::~home() {
    for (int i = devices.size() - 1; i >= 0; i--) {
        if (devices.at(i) != nullptr) {
            delete devices.at(i);
            devices.at(i) = nullptr;
        }
        devices.pop_back();
    }
}