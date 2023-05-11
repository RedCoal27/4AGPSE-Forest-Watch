#include <Arduino.h>
#include "temperature_LM35DZ.h"
#include "photo.h"
#include "Adafruit_AM2320.h"

#include "STM32LowPower.h"
#include <STM32RTC.h>
#include "motion.h"

#include <LecteurSD.h>

#include "_Lora.h"
#include "TSL2561.h"

const int chipSelectPin = A7; // Mettre le numéro de broche correspondant à votre module SD
const char* data_file = "data.csv";
const char* motion_file = "motion.csv";
LecteurSD lecteurSD(chipSelectPin);
Adafruit_AM2320 am2320 = Adafruit_AM2320();


ICM20602 icm20602(0x69);


// /* Get the rtc object */
STM32RTC& rtc = STM32RTC::getInstance();

_Lora lora;




// Variables for RTC configurations
static byte seconds = 0;
static byte minutes = 49;
static byte hours = 17;

static byte weekDay = 2;
static byte day = 2;
static byte month = 5;
static byte year = 23;


void mesure(){
  //int pin = A0;

  CTemperature T(A1); //initialize a temperature sensor in I2C

  // Serial.println("aaaaaaaaaaa"); //print the value read by the sensor
  T.Read(); //print the temperature in °C

  String data = "d;";
  //rtc date
  data += String(rtc.getDay()) + "/" + String(rtc.getMonth()) + "/" + String(rtc.getYear()) + ";";
  data += String(int(T.GetTemperature())) + ";";  

  int temp = am2320.readTemperature();
  delay(100); // d'après la datasheet, il faut attendre un court délai entre deux mesures. Sinon, la mesure ne se fait pas correctement.
  int hum = am2320.readHumidity();

  data += String(temp) + ";";
  data += String(hum) + ";";


  TSL2561 tsl2561;
  data += String(tsl2561.readLux());


  lecteurSD.writeRow(data_file,";" +data);
  lora.send(data);

  //toggle built-in LED
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}


//interrupt on pin D9
void interruption()
{
  // disable interrupt
  detachInterrupt(D9);
  float x,y,z;
  icm20602.readAccelData(x, y, z);

  String data = "m;";
  data += String(x) + ";" + String(y) + ";" + String(z) + ";";
  lecteurSD.writeRow(motion_file, data);
  lora.send(data);
  // enable interrupt
  delay(250);
  attachInterrupt(D9, interruption, RISING);
}

bool should_wake = false;

void alarm(void* data) {
  should_wake = true;
}

void setup()
{
  uint16_t test = 0;
  // Serial.begin(115200);
  rtc.begin();
  rtc.setTime(hours, minutes, seconds);
  rtc.setDate(weekDay, day, month, year);

  icm20602.begin();
  icm20602.start_measurements();
  icm20602.setup_interrupt();

  attachInterrupt(D9, interruption, RISING);

  //A1 as input
  pinMode(A1, INPUT);
  am2320.begin(); //initialiser le capteur de temperature AM2320

  // Low-level CS pin initialization
  lecteurSD.begin(); // Initialiser la carte SD

      // Configure low power
  LowPower.begin();

    //wake up alarm in 5 seconds
  LowPower.enableWakeupFrom(&rtc, alarm);
  delay(1000);
  // Serial.println("Setup done");
}

void wait_second(unsigned long TimeToSleep=5){
  // Configure first alarm in 2 second then it will be done in the rtc callback
  rtc.setAlarmEpoch( rtc.getEpoch() + TimeToSleep);

  while (should_wake == false) {
    LowPower.deepSleep();
  } 
  should_wake = false;
}


void loop() 
{

  Photo Camera;
  // turn on the camera
  Camera.power_on();
  wait_second(5);
  // focus the camera
  Camera.focus(1000);
  // take a picture
  Camera.take_picture();
  wait_second(3);
  // // turn off the camera
  Camera.power_off();
  // //lire mesure
  mesure();

  wait_second(15);
}
