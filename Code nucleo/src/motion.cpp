#include "motion.h"

ICM20602::ICM20602()
{
}


ICM20602::ICM20602(uint8_t address = 0x68)
{
    this->address = address;
}

ICM20602::ICM20602(uint8_t address = 0x68, uint8_t sda = D4, uint8_t scl = D5)
{
    this->sda = sda;
    this->scl = scl;
    this->address = address;
}

ICM20602::~ICM20602()
{
}

void ICM20602::begin()
{
    Wire.begin();

}

// Fonction pour écrire dans un registre
void ICM20602::write_register(uint8_t registerAddress, uint8_t data)
{
    Wire.beginTransmission(address);
    Wire.write(registerAddress);
    Wire.write(data);
    Wire.endTransmission();
}



// Fonction pour lire un registre 16 bits
int16_t ICM20602::read_register(uint8_t reg)
{
    int16_t value;
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(address, (uint8_t)2);
    value = Wire.read() << 8 | Wire.read();
    Wire.endTransmission();
    return value;
}


void ICM20602::start_measurements()
{
    // Sortir du mode veille en mettant le bit SLEEP à 0 dans le registre PWR_MGMT_1
    write_register(PWR_MGMT_1, 0x00);
    delay(100); // Attendre un instant pour que le composant sorte du mode veille
    write_register(ACCEL_CONFIG, 0x10); // Définir l'accéléromètre sur une plage de ±8g
    // Étape 2: Configuration de l'accéléromètre
    write_register(ACCEL_CONFIG2, 0x39);
}

void ICM20602::setup_interrupt()
{
    // Étape 1: S'assurer que l'accéléromètre fonctionne
    write_register(PWR_MGMT_1, 0x00);
    write_register(PWR_MGMT_2, 0x07);
    delay(100);

    // Étape 2: Configuration de l'accéléromètre
    write_register(ACCEL_CONFIG2, 0x09);

    // Étape 3: Activer l'interruption de mouvement
    write_register(INT_ENABLE, 0xE0);

    // Étape 4: Définir le seuil de mouvement
    write_register(ACCEL_WOM_X_THR, X_THRESHOLD_VALUE);
    write_register(ACCEL_WOM_Y_THR, Y_THRESHOLD_VALUE);
    write_register(ACCEL_WOM_Z_THR, Z_THRESHOLD_VALUE);

    // Étape 5: Définir le mode d'interruption
    write_register(ACCEL_INTEL_CTRL, 0x82);


    // Étape 7: Définir la fréquence de réveil
    write_register(SMPLRT_DIV, 0x04); // Par exemple, SMPLRT_DIV = 4, fréquence de réveil = 100Hz

    // Étape 8: Activer le mode Cycle (mode basse consommation de l'accéléromètre)
    write_register(PWR_MGMT_1, 0x20);
}



void ICM20602::readAccelData(float &x, float &y, float &z)
{
    int16_t _x = read_register(ACCEL_XOUT_H);
    int16_t _y = read_register(ACCEL_YOUT_H);
    int16_t _z = read_register(ACCEL_ZOUT_H);

    x = convertToM_s2(_x);
    y = convertToM_s2(_y);
    z = convertToM_s2(_z);
}

float ICM20602::convertToM_s2(int16_t raw_value)
{
    float acc_sensitivity = 4096.0; // Sensibilité pour la plage de ±2g (modifiez cette valeur si vous utilisez une autre plage de mesure)
    float g = 9.81; // Accélération due à la gravité
    float acc_m_s2 = (float(raw_value) / acc_sensitivity) * g;
    return acc_m_s2;
}