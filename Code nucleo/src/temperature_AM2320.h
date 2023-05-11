//classe servant à la mesure de température

#pragma once
#include <Wire.h>
using namespace std;


class CTemperature_AM2320
{
private:
	int m_val_temp;
	int m_val_hum;
	float m_temperature;
	float m_humidite;
    //initiations des données membres pour la connexion I2C
	int m_SDA_pin;
	int m_SCL_pin;

public:
	CTemperature_AM2320();
	~CTemperature_AM2320();
	CTemperature_AM2320(const CTemperature_AM2320& T);
	CTemperature_AM2320(int SDA_pin, int SCL_pin);

    //la fonction Read() permet de lire la valeur mesurée de la température et la retourne
    int Read();

    //la fonction Convertir() permet de convertir la valeur mesurée en température en °C
	void Convert();

    //la fonction GetTemperature() permet d'afficher la valeur de la température mesurée en °C
    double GetTemperature();
	
	//la fonction GetHumidity() permet d'afficher la valeur de l'humidité en %
	double GetHumidity();
};