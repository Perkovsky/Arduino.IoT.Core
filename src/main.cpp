#include <Arduino.h>
#include <WiFiMulti.h>
#include <SdFat.h>
#include <uRTCLib.h>
#include "NtpDateTimeProvider.hpp"
#include "LoggerFactory.hpp"
#include "SettingsAccessor.hpp"

#include "DefaultDateTimeProvider.hpp"

WiFiMulti wifiMulti;
SdFat sd;
uRTCLib rtc(0x68);

//NtpDateTimeProvider dateTimeProvider;
DefaultDateTimeProvider dateTimeProvider;
LoggerFactory logger(dateTimeProvider);

void connectToWiFi() {
  const char* ssid = "Verizon_4CGXRN";
  const char* password = "famous9-fox-apt";

  wifiMulti.addAP(ssid, password);
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(100);
  }
}

void setup() {
  Serial.begin(9600);
  URTCLIB_WIRE.begin();
  sd.begin(4, SPI_HALF_SPEED);

  logger.writeToSerial("Debug", Serial);
  logger.writeToSdCard("Error", sd);

  // SettingsAccessor settingsAccessor(logger, sd);
  // Settings settings = settingsAccessor.getSettings();
  // logger.logInfo(settings.logLevel);
  // logger.logInfo(settings.wifi.ssid);


  connectToWiFi();
  logger.logInfo("WiFi has been connected");
}

void loop() {
  logger.logInfo("ping");
  delay(1000);
}