#pragma once
// class for motion sensor icm-20602
#include <Arduino.h>
#include <Wire.h>

// Adresse I2C du capteur ICM-20602
#define ICM20602_ADDR 0x68

// Registres ICM-20602
#define PWR_MGMT_1 0x6B       // Gestion de l'alimentation, réinitialisation du dispositif et activation du mode veille
#define PWR_MGMT_2 0x6C       // Configuration des modes de veille pour l'accéléromètre et le gyroscope
#define ACCEL_CONFIG 0x1C     // Configuration de l'accéléromètre
#define ACCEL_CONFIG2 0x1D    // Configuration du filtre passe-bas de l'accéléromètre et de la fréquence d'échantillonnage
#define INT_ENABLE 0x38       // Activer ou désactiver les sources d'interruption spécifiques
#define ACCEL_WOM_X_THR 0x20  // Registre pour définir la valeur de seuil pour l'interruption Wake-On-Motion de l'axe X
#define ACCEL_WOM_Y_THR 0x21  // Registre pour définir la valeur de seuil pour l'interruption Wake-On-Motion de l'axe Y
#define ACCEL_WOM_Z_THR 0x22  // Registre pour définir la valeur de seuil pour l'interruption Wake-On-Motion de l'axe Z
#define ACCEL_INTEL_CTRL 0x69 // Contrôle de l'intelligence matérielle de l'accéléromètre (mode d'interruption et activation)
#define SMPLRT_DIV 0x19       // Diviseur de la fréquence d'échantillonnage

// Registres de l'accéléromètre
#define ACCEL_XOUT_H 0x3B     // Registre de lecture de l'accélération de l'axe X
#define ACCEL_XOUT_L 0x3C     // Registre de lecture de l'accélération de l'axe X
#define ACCEL_YOUT_H 0x3D     // Registre de lecture de l'accélération de l'axe Y
#define ACCEL_YOUT_L 0x3E     // Registre de lecture de l'accélération de l'axe Y
#define ACCEL_ZOUT_H 0x3F     // Registre de lecture de l'accélération de l'axe Z
#define ACCEL_ZOUT_L 0x40     // Registre de lecture de l'accélération de l'axe Z


// Valeurs de seuil pour l'interruption
#define X_THRESHOLD_VALUE 0xFF // Par exemple, 10 (0x0A) en unités LSB
#define Y_THRESHOLD_VALUE 0xFF // Par exemple, 10 (0x0A) en unités LSB
#define Z_THRESHOLD_VALUE 0xFF // Par exemple, 10 (0x0A) en unités LSB




class ICM20602
{
private:
    uint8_t sda = D4;
    uint8_t scl = D5;
    uint8_t address = 0x68;
    void write_register(uint8_t registerAddress, uint8_t data);
    int16_t read_register(uint8_t reg);
public:
    ICM20602();
    ICM20602(uint8_t address);
    ICM20602(uint8_t address, uint8_t sda, uint8_t scl);
    ~ICM20602();
    void begin();
    void start_measurements();
    void setup_interrupt();
    void readAccelData(float &x, float &y, float &z);
    float convertToM_s2(int16_t raw_value);
};
