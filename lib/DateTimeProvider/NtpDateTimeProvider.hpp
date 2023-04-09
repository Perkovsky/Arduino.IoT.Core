//////////////////////////////////////////////////////////////
//                                                          //
//     Doesn't work correctly. Refactoring is required.     //    
//                                                          //
//////////////////////////////////////////////////////////////

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
        sprintf(timestamp, "20%02d-%02d-%02d %02d:%02d:%02d", timeInfo.tm_year, timeInfo.tm_mon, timeInfo.tm_mday, timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
        return String(timestamp);
    }
};