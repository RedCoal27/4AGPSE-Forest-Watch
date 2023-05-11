#include "temperature_AM2320.h"
#include <Arduino.h>


CTemperature_AM2320::CTemperature_AM2320()
{
    m_val_temp = 0;
    m_val_hum = 0;
    m_temperature = 0;
    m_humidite = 0;
    m_SDA_pin = 0;
    m_SCL_pin = 0;
}

CTemperature_AM2320::~CTemperature_AM2320()
{
    
}

CTemperature_AM2320::CTemperature_AM2320(const CTemperature_AM2320& T)
{
    m_val_temp = T.m_val_temp;
    m_val_hum = T.m_val_hum;
    m_temperature = T.m_temperature;
    m_humidite = T.m_humidite;
    m_SDA_pin = T.m_SDA_pin;
    m_SCL_pin = T.m_SCL_pin;
}

CTemperature_AM2320::CTemperature_AM2320(int SDA_pin, int SCL_pin)
{
    m_SDA_pin = SDA_pin;
    m_SCL_pin = SCL_pin;
}

int CTemperature_AM2320::Read()
{
    //m_val = digitalRead(m_SDA_pin);

    return m_val_temp, m_val_hum;
}

void CTemperature_AM2320::Convert()
{
    m_temperature = m_val_temp/10;
    m_humidite = m_val_hum/10;
}

double CTemperature_AM2320::GetTemperature()
{
    return m_temperature;
}

double CTemperature_AM2320::GetHumidity()
{
    return m_humidite;
}