#ifndef HOME_H
#define HOME_H
#include "smartlight.h"
#include "device.h"
#include <vector>
#include <string>


class home
{
    private:
        string ownerName;
        int numDevices;
        vector<device*> devices;
    public:
        home(); //default constructor
        home(string _ownerName); //overloaded constructor
        home(const home& RHS); //copy constructor
        home & operator = (const home & RHS); //copy assignment operator
        home & loadFromFile(string filename); //loads a home from a text file
        void save(const std::string& filename) const; //saves a home to a text file
        string getOwnerName(); 
        void setOwnerName(string _ownerName);
        int getNumDevices();
        void addDevice(const device & _device); //adds a device to the home
        void removeDevice(int _deviceID); //removes a device from the home by deviceID
        void changeBrightness(int _deviceID, int newBrightness); //changes brightness of a smartlight by entering the deviceID
        void toggleDevice(int _deviceID, bool turnOn); //turns a device on or off by entering the deviceID
        void printDevices(); //prints all devices in the home
        ~home();

};

#endif