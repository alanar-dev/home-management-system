#include "device.h"
#include <iostream>

using namespace std;

device::device()
{
    deviceID = 0;
    name = "Unknown";
    location = "Unknown";
    isOn = false;
}

device::device(int _id, string _name, string _location)
{
    deviceID = _id;
    name = _name;
    location = _location;
    isOn = false;
}

int device::getDeviceID()
{
    return deviceID;
}

void device::setDeviceID(int _id)
{
    deviceID = _id;
}

string device::getName()
{
    return name;
}

void device::setName(string _name)
{
    name = _name;
}

string device::getLocation()
{
    return location;
}

void device::setLocation(string _location)
{
    location = _location;
}

bool device::getIsOn()
{
    return isOn;
}

void device::setIsOn(bool _isOn)
{
    isOn = _isOn;
}

void device::print()
{
    cout << "Device ID: " << deviceID << endl;
    cout << "Name: " << name << endl;
    cout << "Location: " << location << endl;
    cout << "Status: " << (isOn ? "On" : "Off") << endl;
}