#include "smartlight.h"
#include <iostream>

using namespace std;

smartlight::smartlight() : device()
{
    brightness = 0;
}

smartlight::smartlight(int _id, string _name, string _location, int _brightness) : device(_id, _name, _location)
{
    brightness = _brightness;
}

int smartlight::getBrightness()
{
    return brightness;
}

void smartlight::setBrightness(int _brightness)
{
    brightness = _brightness;
}

void smartlight::print()
{
    device::print();
    cout << "Brightness: " << brightness << endl;
}