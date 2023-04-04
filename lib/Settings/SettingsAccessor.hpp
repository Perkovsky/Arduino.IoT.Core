#pragma once

#include <String.h>
#include <Arduino.h>
#include <SdFat.h>
#include <ArduinoJson.h>
#include "LoggerFactory.hpp"
#include "Settings.hpp"

class SettingsAccessor {
private:
    const String FIlE_NAME = "settings.json";
    LoggerFactory& _logger;
    SdFat& _sd;

public:
    SettingsAccessor(LoggerFactory& logger, SdFat& sd) : _logger(logger), _sd(sd) {}

    Settings getSettings() {
        Settings settings;

        Serial.println("Start--");

        if (!_sd.exists(FIlE_NAME)) {
            _logger.logError(FIlE_NAME + " does not exist");
            return settings;
        }

        Serial.println("Exists--");

        File file = _sd.open(FIlE_NAME, FILE_READ);
        if (!file) {
            _logger.logError("Failed to open " + FIlE_NAME);
            file.close();
            return settings;
        }

        Serial.println("Opened--");

        StaticJsonDocument<100> doc;
        DeserializationError error = deserializeJson(doc, file);
        if (error) {
            _logger.logError("Failed to parse " + FIlE_NAME);
            
            Serial.println("Error--");
            Serial.println(error.c_str());

            file.close();
            doc.clear();

            return settings;
        }


        Serial.println("JSON Deserialized--");


        // settings.logLevel = doc["logLevel"].as<String>();
        // settings.wifi.ssid = doc["wifi"]["ssid"].as<String>();
        // settings.wifi.password = doc["wifi"]["password"].as<String>();
        // settings.ethernet.mac = doc["ethernet"]["mac"].as<String>();
        // settings.telegram.botId = doc["telegram"]["botId"].as<String>();
        // settings.telegram.chatId = doc["telegram"]["chatId"].as<String>();


        settings.logLevel = "logLevel";
        settings.wifi.ssid = "wifi-ssid";
        settings.wifi.password = "wifi-password";
        settings.ethernet.mac = "ethernet-mac";
        settings.telegram.botId = "telegram-botId";
        settings.telegram.chatId = "telegram-chatId";

        file.close();
        doc.clear();

        Serial.println("Cleared--");

        return settings;
    }
};