#pragma once

#include <Arduino.h>
#include <String.h>
#include <HTTPClient.h>
#include "BaseLogger.hpp"

class ElasticsearchLogger final : public BaseLogger {
private:
    const String& _baseUrl;
    HTTPClient* _httpClient;

    String getUrl(const String& uri = String()) {
        String indexName = "log";
        String url(_baseUrl);
        url.reserve(_baseUrl.length() + indexName.length() + uri.length() + 2);
        url += "/";
        url += indexName;
        url += uri;
        return url;
    }

    bool DoesIndexExist() {
        String url = getUrl();
        _httpClient->begin(url);
        int httpCode = _httpClient->GET();
        _httpClient->end();
        return httpCode == HTTP_CODE_OK;
    }

    void createIndex() {
        if (DoesIndexExist()) {
            return;
        }

        String url = getUrl();
        _httpClient->begin(url);
        _httpClient->addHeader("Content-Type", "application/json");

        // Define the index mapping
        String indexMapping = F("{\"mappings\": {"
                              "\"properties\": {"
                              "\"timestamp\": {\"type\": \"date\"},"
                              "\"level\": {\"type\": \"keyword\"},"
                              "\"message\": {\"type\": \"text\"}"
                              "}}}");

        int createIndexCode = _httpClient->PUT(indexMapping);
        _httpClient->end();
    }

public:
    ElasticsearchLogger(const LogLevel logLevel, String& url, AbstractDateTimeProvider& dateTimeProvider, TelegramNotifier* notifier)
        : BaseLogger(logLevel, dateTimeProvider, notifier), _baseUrl(url)
    {
        _httpClient = new HTTPClient();
    }

protected:
    ResponseLog log(const String& logLevel, const String& timestamp, const String& message) override {
        createIndex();
        
        String url = getUrl("/_doc");
        _httpClient->begin(url);
        _httpClient->addHeader("Content-Type", "application/json");

        String jsonPayload("{\"timestamp\":\"");
        jsonPayload.reserve(timestamp.length() + logLevel.length() + message.length() + 53);
        jsonPayload += timestamp;
        jsonPayload += "\",\"level\":\"";
        jsonPayload += logLevel;
        jsonPayload += "\",\"message\":\"";
        jsonPayload += message;
        jsonPayload += "\"}";

        int httpCode = _httpClient->POST(jsonPayload);
        String response = _httpClient->getString(); // successful or failed message
        _httpClient->end();
        
        String loggerName = F("ElasticsearchLogger");
        if (httpCode == HTTP_CODE_CREATED) {
           return getSuccessfulResponseLog(loggerName, response);
        }
        
        return getFailedResponseLog(loggerName, response);
    }
};