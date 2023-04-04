#pragma once

#include <String.h>
#include <Arduino.h>
#include <SD.h>
#include "BaseLogger.hpp"

class SdCardLogger final : public BaseLogger {
private:
    const String FIlE_NAME = "log001.txt";
    const SDClass& _sd;

public:
    SdCardLogger(const LogLevel logLevel, const SDClass& sd, uRTCLib* rtc = nullptr)
        : BaseLogger(logLevel, rtc), _sd(sd) {}

protected:
    bool log(const String& message) override {
        File file = SD.open(FIlE_NAME, FILE_WRITE);
        
        if (!file)
            return false;

        file.println(message);
        file.close();
        
        return true;
    }
};