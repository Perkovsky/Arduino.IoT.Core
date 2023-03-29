#pragma once

#include <String.h>
#include "LogLevel.hpp"

class BaseLogger {
private:
    const LogLevel _logLevel;

    static String getTimestamp() {
        return String(millis());
    }

    static String toString(const LogLevel logLevel) {
        switch (logLevel) {
            case LogLevel::Debug:
                return "DBG";
            case LogLevel::Warning:
                return "WRN";
            case LogLevel::Error:
                return "ERR";
            default:
                return "INF";
        }
    }

    static String buildLogMessage(const LogLevel logLevel, const String& message) {
        const auto timestamp = getTimestamp();
        const auto strLogLevel = toString(logLevel);
        return "[" + timestamp + " " + strLogLevel + "] " + message;
    }

    void log(const LogLevel logLevel, const String& message)
    {
        if (logLevel < _logLevel)
            return;

        const String logMessage = buildLogMessage(logLevel, message);
        log(logMessage);
    }

protected:
    explicit BaseLogger(LogLevel logLevel) : _logLevel(logLevel) {}

    virtual ~BaseLogger() = default;

    virtual void log(const String& message) = 0;

public:
    virtual void setup() = 0;

    void logDebug(const String& message) {
        log(LogLevel::Debug, message);
    }

    void logInfo(const String& message) {
        log(LogLevel::Info, message);
    }

    void logWarning(const String& message) {
        log(LogLevel::Warning, message);
    }

    void logError(const String& message) {
        log(LogLevel::Error, message);
    }
};