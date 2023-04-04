#include <Arduino.h>
#include <uRTCLib.h>
#include <SD.h>
#include "LoggerFactory.hpp"

uRTCLib rtc(0x68);
LoggerFactory _logger(&rtc);

void setup() {
  Serial.begin(9600);
  URTCLIB_WIRE.begin();
  SD.begin(4);

  _logger.writeToSerial("Debug", Serial);
  _logger.writeToSdCard("Error", SD);
}

void loop() {
  rtc.refresh();
  _logger.logInfo("ping");
  delay(1000);
}