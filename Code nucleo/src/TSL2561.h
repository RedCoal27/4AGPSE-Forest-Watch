#pragma once


#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_TSL2561_U.h>

class TSL2561
{
public:
    TSL2561();
    ~TSL2561();
    void configureSensor();
    uint32_t readLux();
};


