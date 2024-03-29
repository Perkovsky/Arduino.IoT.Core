#pragma once

#include <String.h>
#include "AbstractDateTimeProvider.hpp"
#include "SerialLogger.hpp"
#include "SdCardLogger.hpp"
#include "ElasticsearchLogger.hpp"

class LoggerFactory {
private:
    AbstractDateTimeProvider& _dateTimeProvider;
    TelegramNotifier& _notifier;
    HTTPClient& _httpClient;
    BaseLogger* _loggers[3];
    unsigned char _count = 0;

    static LogLevel toLogLevel(const String& logLevel) {
        if (logLevel == F("Debug"))
            return LogLevel::Debug;
        
        if (logLevel == F("Info"))
            return LogLevel::Info;
        
        if (logLevel == F("Warning"))
            return LogLevel::Warning;

        return LogLevel::Error;
    }

public:
    LoggerFactory(AbstractDateTimeProvider& dateTimeProvider, TelegramNotifier& notifier, HTTPClient& httpClient)
        : _dateTimeProvider(dateTimeProvider), _notifier(notifier), _httpClient(httpClient) {}

    void writeToSerial(const String& logLevel, Stream& stream) {
        _loggers[_count++] = new SerialLogger(toLogLevel(logLevel), stream, _dateTimeProvider, _notifier);
    }

    void writeToSdCard(const String& logLevel, SdFat& sd) {
        _loggers[_count++] = new SdCardLogger(toLogLevel(logLevel), sd, _dateTimeProvider, _notifier);
    }

    void writeToElasticserach(const String& logLevel, const String& url) {
        _loggers[_count++] = new ElasticsearchLogger(toLogLevel(logLevel), url, _dateTimeProvider, _notifier, _httpClient);
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

    void logError(const String& message) {
        for (int i = 0; i < _count; i++) {
            _loggers[i]->logError(message);
        }
        _notifier.notify(message);
    }
};