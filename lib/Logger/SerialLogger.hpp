#pragma once

#include <Arduino.h>
#include "ResponseLog.hpp"
#include "BaseLogger.hpp"

class SerialLogger final : public BaseLogger {
private:
    Stream& _stream;

public:
    SerialLogger(const LogLevel logLevel, Stream& stream, AbstractDateTimeProvider& dateTimeProvider, TelegramNotifier& notifier)
        : BaseLogger(logLevel, dateTimeProvider, notifier), _stream(stream) {}

protected:
    ResponseLog log(const String& logLevel, const String& timestamp, const String& message) override {
        _stream.println(buildLogMessage(logLevel, timestamp, message));
        return getSuccessfulResponseLog(F("SerialLogger"));
    }
};