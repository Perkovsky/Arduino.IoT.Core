#pragma once

#include <String.h>
#include <uRTCLib.h>
#include "LogLevel.hpp"

class BaseLogger {
private:
    const LogLevel _logLevel;
    uRTCLib* _rtc;

    String getTimestampFromRtc() {
        char timestamp[20];
        sprintf(timestamp, "20%02d-%02d-%02d %02d:%02d:%02d", _rtc->year(), _rtc->month(), _rtc->day(), _rtc->hour(), _rtc->minute(), _rtc->second());
        return String(timestamp);
    }

    String getTimestamp() {
        if (_rtc != nullptr)
            return getTimestampFromRtc();

        return String(millis());
    }

    static String toString(const LogLevel& logLevel) {
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

    String buildLogMessage(const LogLevel& logLevel, const String& message) {
        const auto timestamp = getTimestamp();
        const auto strLogLevel = toString(logLevel);
        return "[" + timestamp + " " + strLogLevel + "] " + message;
    }

    void log(const LogLevel& logLevel, const String& message)
    {
        if (logLevel < _logLevel)
            return;

        const String logMessage = buildLogMessage(logLevel, message);
        if  (!log(logMessage))
        {
            // _notifier.Send("Cannot log message: '" + message + "'");
        }
    }

protected:
    explicit BaseLogger(const LogLevel logLevel, uRTCLib* rtc = nullptr) : _logLevel(logLevel), _rtc(rtc) {}

    virtual ~BaseLogger() = default;

    virtual bool log(const String& message) = 0;

public:
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