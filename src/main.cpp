#include <Arduino.h>
#include <SdFat.h>
#include <uRTCLib.h>
#include "WiFiManager.hpp"
#include "TelegramNotifier.hpp"
#include "DefaultDateTimeProvider.hpp"
#include "LoggerFactory.hpp"
#include "SettingsAccessor.hpp"

SdFat sd;
WiFiManager* wifiManager;
TelegramNotifier* notifier;

DefaultDateTimeProvider dateTimeProvider;
LoggerFactory* logger;

void setup() {
    Serial.begin(9600);
    URTCLIB_WIRE.begin();
    sd.begin(4, SPI_HALF_SPEED);


    // SettingsAccessor settingsAccessor(logger, sd);
    // Settings settings = settingsAccessor.getSettings();
    // logger.logInfo(settings.logLevel);
    // logger.logInfo(settings.wifi.ssid);

    String ssid = F("Verizon_4CGXRN");
    String password = F("famous9-fox-apt");
    String botId = "6260968708:AAFmiglC7q1HcLDWG1VGG8L6LAyc_brEVBE";
    String chatId = "-1001848360474";

    
    notifier = new TelegramNotifier(botId, chatId);
    logger = new LoggerFactory(dateTimeProvider, notifier);
    logger->writeToSerial("Debug", Serial);
    //logger->writeToSdCard("Error", sd);

    wifiManager = new WiFiManager(ssid, password, *logger);
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