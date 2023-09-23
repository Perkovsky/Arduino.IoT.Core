#pragma once

#include <SdFat.h>
#include "ResponseLog.hpp"
#include "BaseLogger.hpp"

class SdCardLogger final : public BaseLogger {
private:
    const String FIlE_NAME = F("log001.txt");
    SdFat& _sd;

public:
    SdCardLogger(const LogLevel logLevel, SdFat& sd, AbstractDateTimeProvider& dateTimeProvider, TelegramNotifier& notifier)
        : BaseLogger(logLevel, dateTimeProvider, notifier), _sd(sd) {}

protected:
    ResponseLog log(const String& logLevel, const String& timestamp, const String& message) override {
        File file = _sd.open(FIlE_NAME, FILE_WRITE);
        
        String loggerName = F("SdCardLogger");
        if (!file) {
            return getFailedResponseLog(loggerName);
        }

        file.println(buildLogMessage(logLevel, timestamp, message));
        file.close();
        
        return getSuccessfulResponseLog(loggerName);
    }
};