#include <Arduino.h>
#include <uRTCLib.h>
#include <SdFat.h>
#include "LoggerFactory.hpp"

const uint8_t CS_PIN = 4;
const unsigned long BAUD = 9600;

uRTCLib rtc(0x68);
SdFat sd;
LoggerFactory _logger(&rtc);

void setup() {
  Serial.begin(BAUD);
  URTCLIB_WIRE.begin();
  sd.begin(CS_PIN, SPI_HALF_SPEED);

  _logger.writeToSerial("Debug", Serial);
  _logger.writeToSdCard("Error", sd);
}

void loop() {
  rtc.refresh();
  _logger.logInfo("ping");
  delay(1000);
}