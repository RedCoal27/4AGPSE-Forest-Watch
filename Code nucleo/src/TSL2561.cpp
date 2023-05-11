#include "TSL2561.h"


Adafruit_TSL2561_Unified TSL(TSL2561_ADDR_FLOAT, 12345);
TSL2561::TSL2561(){

    configureSensor();
}

TSL2561::~TSL2561()
{
}


void TSL2561::configureSensor(){
  TSL.begin();
    /* You can also manually set the gain or enable auto-gain support */
  TSL.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
  /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
  TSL.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
}

uint32_t TSL2561::readLux(){
    /* Get a new sensor event */ 
  sensors_event_t event;
  TSL.getEvent(&event);
  /* Display the results (light is measured in lux) */
  return event.light;
}

