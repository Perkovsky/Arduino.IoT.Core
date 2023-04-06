#include <Arduino.h>
#include <SdFat.h>
#include <uRTCLib.h>
#include "WiFiManager.hpp"
#include "TelegramNotifier.hpp"
#include "DefaultDateTimeProvider.hpp"
#include "LoggerFactory.hpp"
#include "SettingsAccessor.hpp"

DefaultDateTimeProvider dateTimeProvider;
SdFat sd;
TelegramNotifier* notifier;
LoggerFactory* logger;
WiFiManager* wifiManager;


void setup() {
    Serial.begin(9600);
    URTCLIB_WIRE.begin();
    sd.begin(4, SPI_HALF_SPEED);

    // settings
    SettingsAccessor settingsAccessor(sd);
    Settings settings = settingsAccessor.getSettings();
    
    // notifier
    notifier = new TelegramNotifier(settings.telegram.botId, settings.telegram.chatId);
    
    // logger
    logger = new LoggerFactory(dateTimeProvider, notifier);
    logger->writeToSerial(settings.logLevel.serial, Serial);
    logger->writeToSdCard(settings.logLevel.sd, sd);

    // WiFi
    wifiManager = new WiFiManager(settings.wifi.ssid, settings.wifi.password, *logger);
    wifiManager->connect();
    delay(1000);
    wifiManager->checkConnection();
}

void restart() {
    logger->logInfo("Restarting in 10 seconds");
    delay(10000);
    ESP.restart();
}

void loop() {
    logger->logInfo("ping");
    delay(1000);
    //restart();
}