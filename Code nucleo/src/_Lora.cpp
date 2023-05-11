#include "_LoRa.h"

_Lora::_Lora()
{
    m_LoRa.setPins(LORA_DEFAULT_SS_PIN, LORA_DEFAULT_RESET_PIN, LORA_DEFAULT_DIO0_PIN); //definir os pinos SS, RST e DIO0
}

_Lora::_Lora(uint8_t cs, uint8_t reset, uint8_t dio0)
{
    m_LoRa.setPins(cs, reset, dio0); //definir os pinos SS, RST e DIO0
}   

_Lora::~_Lora()
{
}

bool _Lora::begin(){
    m_LoRa.setPins(LORA_DEFAULT_SS_PIN, LORA_DEFAULT_RESET_PIN, LORA_DEFAULT_DIO0_PIN); //definir os pinos SS, RST e DIO0
    m_LoRa.setSPIFrequency(200000);
    if (!m_LoRa.begin(LORA_DEFAULT_FREQUENCY)) {
        // Serial.println("Starting LoRa failed!");
        return false;
    }
    // m_LoRa.setSignalBandwidth(LORA_DEFAULT_BANDWIDTH);
    // m_LoRa.setCodingRate4(LORA_DEFAULT_CODINGRATE);
    m_LoRa.setSpreadingFactor(LORA_DEFAULT_SPREADINGFACTOR);
    m_LoRa.setTxPower(LORA_DEFAULT_TXPOWER);
    return true;
}

bool _Lora::stop(){
    m_LoRa.end();
    delay(100);
    return true;
}

void _Lora::send(String message){
    begin();
    for(uint16_t i = 0; i < 1; i++){
        m_LoRa.beginPacket();
        m_LoRa.print(message); 
        m_LoRa.endPacket(); 
        delay(100);
    }
    stop();
}
