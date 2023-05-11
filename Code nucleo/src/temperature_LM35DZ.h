//classe servant à la mesure de température avec le capteur LM32DZ

#pragma once
#include <Wire.h>
using namespace std;

class CTemperature
{
private:
	int m_val;
	float m_temperature;
    int m_pin;

public:
	CTemperature();
	~CTemperature();
	CTemperature(const CTemperature& T);
	CTemperature(int pin);

    //la fonction Read() permet de lire la valeur mesurée de la température et la retourne
    int Read();

    //la fonction Convertir() permet de convertir la valeur mesurée en température en °C
	float Convert(float val);

    //la fonction GetTemperature() permet d'afficher la valeur de la température mesurée en °C
    float GetTemperature();
};
