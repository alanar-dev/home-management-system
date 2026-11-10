#ifndef DEVICE_H
#define DEVICE_H
#include <string>

using namespace std;

class device
{
    private:
        int deviceID;
        string name;
        string location;
        bool isOn;
        char type = 'D';
    public:
        device();
        device(int _id, string _name, string _location);
        int getDeviceID();
        void setDeviceID(int _id);
        string getName();
        void setName(string _name);
        string getLocation();
        void setLocation(string _location);
        bool getIsOn();
        void setIsOn(bool _isOn); //true for on, false for off
        virtual char getType() const { return 'D'; } //returns 'D' for device, useful in home (container) class
        virtual void print(); //prints device details
};

#endif