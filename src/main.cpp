#include <Arduino.h>
#include "LoggerFactory.hpp"

LoggerFactory* _logger = new LoggerFactory();

void setup() {
  _logger->writeToSerial(LogLevel::Debug);
  _logger->setup();
}

void loop() {
  _logger->logInfo("ping");
  delay(1000);
}