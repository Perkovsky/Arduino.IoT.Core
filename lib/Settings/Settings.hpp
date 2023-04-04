#pragma once

#include <String.h>

struct WiFiSettings {
    String ssid;
    String password;
};

struct EthernetSettings {
    String mac;
};

struct TelegramSettings {
    String botId;
    String chatId;
};

struct Settings {
    String logLevel;
    WiFiSettings wifi;
    EthernetSettings ethernet;
    TelegramSettings telegram;
};