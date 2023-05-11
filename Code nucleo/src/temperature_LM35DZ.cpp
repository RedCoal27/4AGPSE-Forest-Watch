#include "temperature_LM35DZ.h"
#include <Arduino.h>

//classe servant à la mesure de température avec le capteur LM32DZ

CTemperature::CTemperature()
{
    m_val = 0;
    m_temperature = 0;
}

CTemperature::~CTemperature()
{
    
}

CTemperature::CTemperature(const CTemperature& T)
{
    m_val = T.m_val;
    m_temperature = T.m_temperature;
    m_pin = T.m_pin;
}


CTemperature::CTemperature(int pin)
{
    m_pin = pin;
}

int CTemperature::Read()
{
    m_val = analogRead(m_pin);
    return m_val;
}

float CTemperature::Convert(float val)
{
    return val *(3.3 / 1023.0 * 100);
}

float CTemperature::GetTemperature()
{
    //conversion de la valeur mesurée en température en °C
    m_temperature = Convert(m_val);
    return m_temperature;
}
