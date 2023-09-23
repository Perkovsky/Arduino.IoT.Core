#pragma once

#include <String.h>
#include <HTTPClient.h>

class TelegramNotifier {
private:
    const String& _botId;
    const String& _chatId;
    HTTPClient& _httpClient;

public:
    TelegramNotifier(const String& botId, const String& chatId, HTTPClient& httpClient)
        : _botId(botId), _chatId(chatId), _httpClient(httpClient) {}
    
    void notify(const String& message) {
        String url("https://api.telegram.org/bot");
        url.reserve(_botId.length() + _chatId.length() + message.length() + 56);
        url += _botId;
        url += "/sendMessage?chat_id=";
        url += _chatId;
        url += "&text=";
        url += message;

        _httpClient.begin(url.c_str());
        int httpResponseCode = _httpClient.GET();
        _httpClient.end();
    }
};