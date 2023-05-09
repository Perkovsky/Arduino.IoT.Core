#pragma once

#include <Arduino.h>
#include <time.h>
#include "LoggerFactory.hpp"
#include "AbstractDateTimeProvider.hpp"

class NtpDateTimeProvider final : public AbstractDateTimeProvider {
private:
    tm getTimeInfo() {
        struct tm timeInfo;
        getLocalTime(&timeInfo);
        return timeInfo;
    }

public:
    NtpDateTimeProvider() {
        // -14400 => GMT-04:00 in seconds
        configTime(0, -14400, "pool.ntp.org", "time.nist.gov");
    }

    String getTimestamp() override {
        tm timeInfo = getTimeInfo();
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeInfo);
        return String(timestamp);
    }
};