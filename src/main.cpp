#include <Arduino.h>
#include <uRTCLib.h>
#include "LoggerFactory.hpp"

uRTCLib rtc(0x68);
LoggerFactory _logger(&rtc);

void setup() {
  Serial.begin(9600);
  URTCLIB_WIRE.begin();
  _logger.writeToSerial("Debug", Serial);
}

void loop() {
  rtc.refresh();
  _logger.logInfo("ping");
  delay(1000);
}