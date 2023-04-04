#pragma once

#include <String.h>
#include "AbstractDateTimeProvider.hpp"
#include "SerialLogger.hpp"
#include "SdCardLogger.hpp"

class LoggerFactory {
private:
    AbstractDateTimeProvider& _dateTimeProvider;
    BaseLogger* _loggers[2];
    unsigned char _count = 0;

    static LogLevel toLogLevel(const String& logLevel) {
        if (logLevel == "Debug")
            return LogLevel::Debug;
        
        if (logLevel == "Info")
            return LogLevel::Info;
        
        if (logLevel == "Warning")
            return LogLevel::Warning;

        return LogLevel::Error;
    }

public:
    LoggerFactory(AbstractDateTimeProvider& dateTimeProvider): _dateTimeProvider(dateTimeProvider) {}

    void writeToSerial(const String& logLevel, Stream& stream) {
        _loggers[_count++] = new SerialLogger(toLogLevel(logLevel), stream, _dateTimeProvider);
    }

    void writeToSdCard(const String& logLevel, SdFat& sd) {
        _loggers[_count++] = new SdCardLogger(toLogLevel(logLevel), sd, _dateTimeProvider);
    }

    void logDebug(const String& message) const {
        for (int i = 0; i < _count; i++) {
            _loggers[i]->logDebug(message);
        }
    }

    void logInfo(const String& message) const {
        for (int i = 0; i < _count; i++) {
            _loggers[i]->logInfo(message);
        }
    }

    void logWarning(const String& message) const {
        for (int i = 0; i < _count; i++) {
            _loggers[i]->logWarning(message);
        }
    }

    void logError(const String& message) const {
        for (int i = 0; i < _count; i++) {
            _loggers[i]->logError(message);
            // _notifier.Send(message);
        }
    }
};