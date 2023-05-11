#include "LecteurSD.h"

LecteurSD::LecteurSD(int chipSelectPin) :
  _chipSelectPin(chipSelectPin){}

bool LecteurSD::begin() {
  pinMode(_chipSelectPin, OUTPUT); // Chip select pin for SD card
  
  return SD.begin(_chipSelectPin);
}

bool LecteurSD::writeRow(const char* filename, String rowData) {
  File csvFile = SD.open(filename, FILE_WRITE);
  if (csvFile) {
    csvFile.println(rowData);
    csvFile.flush();
    csvFile.close();
    
    return true;
  }
  return false;
}

String LecteurSD::readRow(const char* filename) {
  String rowData = "";
  File csvFile = SD.open(filename, FILE_READ);
  if (csvFile) {
    rowData = csvFile.readStringUntil('\n');
    csvFile.close();
  }
  return rowData;
}

