#pragma once
#include <Arduino.h>

class Photo
{
    private:
        int shutter_pin=D3;
        int focus_pin=D2;
        int power_pin=A2;
    public:
        Photo();
        ~Photo();
        Photo(int shutter_pin, int focus_pin, int power_pin);
        void take_picture();
        void focus(int time);
        void power_on();
        void power_off();
};
