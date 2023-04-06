#pragma once

#include <String.h>
#include <Arduino.h>
#include <SdFat.h>
#include <ArduinoJson.h>
#include "Settings.hpp"

class SettingsAccessor {
private:
    const String FIlE_NAME = "settings.json";
    SdFat& _sd;

public:
    SettingsAccessor(SdFat& sd) : _sd(sd) {}

    Settings getSettings() {
        Settings settings;

        if (!_sd.exists(FIlE_NAME)) {
            Serial.print(FIlE_NAME);
            Serial.println(" does not exist");
            return settings;
        }

        File file = _sd.open(FIlE_NAME, FILE_READ);
        if (!file) {
            file.close();
            Serial.print("Failed to open ");
            Serial.println(FIlE_NAME);
            return settings;
        }

        StaticJsonDocument<512> doc;
        DeserializationError error = deserializeJson(doc, file);
        if (error) {
            Serial.print("Failed to parse ");
            Serial.print(FIlE_NAME);
            Serial.print(". Error: ");
            Serial.println(error.c_str());
            file.close();
            doc.clear();
            return settings;
        }

        settings.logLevel.serial = doc["logLevel"]["serial"].as<String>();
        settings.logLevel.sd = doc["logLevel"]["sd"].as<String>();
        settings.wifi.ssid = doc["wifi"]["ssid"].as<String>();
        settings.wifi.password = doc["wifi"]["password"].as<String>();
        settings.ethernet.mac = doc["ethernet"]["mac"].as<String>();
        settings.telegram.botId = doc["telegram"]["botId"].as<String>();
        settings.telegram.chatId = doc["telegram"]["chatId"].as<String>();

        file.close();
        doc.clear();

        return settings;
    }
};