#include <Arduino.h>
#include <SdFat.h>
#include <uRTCLib.h>
//#include "RtcDateTimeProvider.hpp"
#include "DefaultDateTimeProvider.hpp"
#include "LoggerFactory.hpp"

SdFat sd;
uRTCLib rtc(0x68);
//RtcDateTimeProvider dateTimeProvider(rtc);
DefaultDateTimeProvider dateTimeProvider;
LoggerFactory logger(dateTimeProvider);

void setup() {
  Serial.begin(9600);
  URTCLIB_WIRE.begin();
  sd.begin(4, SPI_HALF_SPEED);

  logger.writeToSerial("Debug", Serial);
  logger.writeToSdCard("Error", sd);

  //rtc.refresh();
  logger.logInfo("Start system");
}

void loop() {
  //rtc.refresh();
  logger.logInfo("ping");
  delay(1000);
}