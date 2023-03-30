#pragma once

#include <String.h>
#include "SerialLogger.hpp"

class LoggerFactory {
private:
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
    void writeToSerial(const String& logLevel, const Stream& stream) {
        _loggers[_count++] = new SerialLogger(toLogLevel(logLevel), stream);
    }

    // void writeToSdCard(const LogLevel logLevel) {
    //     //
    // }

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
        }
    }
};