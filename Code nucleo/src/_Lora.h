#pragma once

#include <Arduino.h>
#include <SPI.h>              // include libraries
#include <LoRa.h>

#define LORA_DEFAULT_SS_PIN D8
#define LORA_DEFAULT_RESET_PIN D7
#define LORA_DEFAULT_DIO0_PIN D6

#define LORA_DEFAULT_FREQUENCY 868100000
#define LORA_DEFAULT_BANDWIDTH 125000
#define LORA_DEFAULT_CODINGRATE 8
#define LORA_DEFAULT_SPREADINGFACTOR 7
#define LORA_DEFAULT_TXPOWER 20

class _Lora
{
private:
    LoRaClass m_LoRa;
public:
    _Lora();
    _Lora(uint8_t cs, uint8_t reset, uint8_t dio0);
    ~_Lora();
    bool begin();
    bool stop();
    void send(String message);
};


