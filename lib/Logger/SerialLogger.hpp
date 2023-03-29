#pragma once

#include <String.h>
#include <Arduino.h>
#include "BaseLogger.hpp"

class SerialLogger final : public BaseLogger {
private:
    const unsigned long _bound;

public:
    SerialLogger(const LogLevel logLevel, const unsigned long bound = 9600): BaseLogger(logLevel), _bound(bound) {}

    void setup() override {
        Serial.begin(_bound);
    }

protected:
    void log(const String& message) override {
        Serial.println(message);
    }
};