#ifndef SMARTLIGHT_H
#define SMARTLIGHT_H
#include "device.h"

class smartlight : public device
{
    private:
        int brightness;
        char type = 'S';
    public:
        smartlight();
        smartlight(int _id, string _name, string _location, int _brightness);
        int getBrightness();
        void setBrightness(int _brightness);
        virtual char getType() const { return 'S'; } //returns 'S' for smartlight, useful in home (container) class
        virtual void print(); //overrides device print function
};


#endif