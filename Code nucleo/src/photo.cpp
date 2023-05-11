#include "photo.h"

Photo::Photo()
{
    //Output pins
    pinMode(shutter_pin, OUTPUT);
    pinMode(focus_pin, OUTPUT);
    pinMode(power_pin, OUTPUT);
}

Photo::~Photo()
{
}

Photo::Photo(int shutter_pin, int focus_pin, int power_pin)
{
    this->shutter_pin = shutter_pin;
    this->focus_pin = focus_pin;
    this->power_pin = power_pin;
    pinMode(shutter_pin, OUTPUT);
    pinMode(focus_pin, OUTPUT);
    pinMode(power_pin, OUTPUT);
}

void Photo::take_picture()
{
    //take a picture
    digitalWrite(shutter_pin, HIGH);
    delay(1000);
    digitalWrite(shutter_pin, LOW);
    delay(500);
}

void Photo::focus(int time)
{
    //focus the camera
    digitalWrite(focus_pin, HIGH);
    delay(time);
    digitalWrite(focus_pin, LOW);
    delay(250);
}

void Photo::power_on()
{
    //turn on the camera
    digitalWrite(power_pin, HIGH);
}

void Photo::power_off()
{
    //turn off the camera
    digitalWrite(power_pin, LOW);
}


