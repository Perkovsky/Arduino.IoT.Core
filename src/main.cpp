#include <Arduino.h>
#include <SdFat.h>
#include <uRTCLib.h>
#include <HTTPClient.h>
#include "WiFiManager.hpp"
#include "TelegramNotifier.hpp"
#include "RtcDateTimeProvider.hpp"
#include "LoggerFactory.hpp"
#include "SettingsAccessor.hpp"

uRTCLib rtc(0x68);
RtcDateTimeProvider dateTimeProvider(rtc);
SdFat sd;
HTTPClient httpClient;
TelegramNotifier* notifier;
LoggerFactory* logger;
WiFiManager* wifiManager;

void setup() {
    Serial.begin(9600);
    sd.begin(4, SPI_HALF_SPEED);
    URTCLIB_WIRE.begin();
    rtc.refresh();

    // settings
    SettingsAccessor settingsAccessor(sd);
    Settings settings = settingsAccessor.getSettings();
    
    // notifier
    notifier = new TelegramNotifier(settings.telegram.botId, settings.telegram.chatId, httpClient);
    
    // logger
    logger = new LoggerFactory(dateTimeProvider, *notifier, httpClient);
    logger->writeToSerial(settings.logLevel.serial, Serial);
    logger->writeToSdCard(settings.logLevel.sd, sd);
    logger->writeToElasticserach(settings.logLevel.elasticsearch, settings.elasticsearchUrl);

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
    rtc.refresh();
    logger->logInfo("ping");
    delay(1000);
    //restart();
}