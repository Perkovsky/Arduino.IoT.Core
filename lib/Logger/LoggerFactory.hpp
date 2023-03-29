#pragma once

#include <String.h>
#include "SerialLogger.hpp"

class LoggerFactory {
private:
    BaseLogger* _loggers[2];
    unsigned char _count = 0;

public:
    void writeToSerial(const LogLevel logLevel, const unsigned long bound = 9600) {
        _loggers[_count++] = new SerialLogger(logLevel, bound);
    }

    // void writeToSdCard(const LogLevel logLevel) {
    //     //
    // }

    void setup() const {
        for (int i = 0; i < _count; i++) {
            _loggers[i]->setup();
        }
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
        }
    }
};