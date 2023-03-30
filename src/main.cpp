#include <Arduino.h>
#include "LoggerFactory.hpp"

LoggerFactory _logger;

void setup() {
  Serial.begin(9600);
  _logger.writeToSerial("Debug", Serial);
}

void loop() {
  _logger.logInfo("ping");
  delay(1000);
}