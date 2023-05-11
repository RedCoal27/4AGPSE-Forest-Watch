#pragma once

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

class LecteurSD {
public:
  LecteurSD(int chipSelectPin);
  bool begin();
  bool writeRow(const char* filename, String rowData);
  String readRow(const char* filename);

private:
  int _chipSelectPin;
};

