#pragma once

#include <Arduino.h>
#include <time.h>
#include "LoggerFactory.hpp"
#include "AbstractDateTimeProvider.hpp"

class NtpDateTimeProvider final : public AbstractDateTimeProvider {
private:
    const char* ntpServer = "pool.ntp.org";
    const long gmtOffset = 0; // in seconds
    const int daylightOffset = -14400; //GMT-04:00 in seconds

    tm getTimeInfo() {
        struct tm timeInfo;
        getLocalTime(&timeInfo);
        return timeInfo;
    }

public:
    NtpDateTimeProvider() {
        configTime(gmtOffset, daylightOffset, ntpServer);
    }

    String getTimestamp() override {
        tm timeInfo = getTimeInfo();
        char timestamp[20];
        sprintf(timestamp, "20%02d-%02d-%02d %02d:%02d:%02d", timeInfo.tm_year, timeInfo.tm_mon, timeInfo.tm_mday, timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
        return String(timestamp);
    }
};