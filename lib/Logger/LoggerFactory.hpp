#pragma once

#include <String.h>
#include "SerialLogger.hpp"
#include "SdCardLogger.hpp"

class LoggerFactory {
private:
    uRTCLib* _rtc;
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
    LoggerFactory(uRTCLib* rtc = nullptr): _rtc(rtc) {}

    void writeToSerial(const String& logLevel, Stream& stream) {
        _loggers[_count++] = new SerialLogger(toLogLevel(logLevel), stream, _rtc);
    }

    void writeToSdCard(const String& logLevel, SdFat& sd) {
        _loggers[_count++] = new SdCardLogger(toLogLevel(logLevel), sd, _rtc);
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