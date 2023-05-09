#pragma once

#include <String.h>
#include <Ethernet.h>
#include <SPI.h>
#include "LoggerFactory.hpp"

class EthernetManager {
private:
    byte (&_mac)[6];
    bool isConnected = false;
    LoggerFactory& _logger;

public:
    EthernetManager(byte (&mac)[6], LoggerFactory& logger)
        : _mac(mac), _logger(logger) {}

    void connect() {
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, LOW);

        Ethernet.init(10);
        Ethernet.begin(_mac);

        if (Ethernet.hardwareStatus() == EthernetNoHardware) {
            _logger.logWarning(F("Ethernet shield was not found"));
            while (true) {
                delay(1); // do nothing, no point running without Ethernet hardware
            }
        }

        if (Ethernet.linkStatus() == LinkOFF) {
            _logger.logWarning("Ethernet cable has not been connected");
            return;
        }

        isConnected = true;
        digitalWrite(LED_BUILTIN, HIGH);
        _logger.logInfo("Ethernet cable has been connected");
        
        // log IP
        auto ip = Ethernet.localIP();
        String infoIP(F("Local IP Address: "));
        infoIP.reserve(35);
        infoIP += ip[0];
        infoIP += ".";
        infoIP += ip[1];
        infoIP += ".";
        infoIP += ip[2];
        infoIP += ".";
        infoIP += ip[3];
        _logger.logInfo(infoIP);
    }

    void checkConnection() {
        EthernetClient client;
        if (client.connect(F("www.google.com"), 80)) {
            _logger.logInfo(F("Ping google.com successful"));
            client.stop();
        } else {
            _logger.logWarning(F("Ping google.com failed"));
        }
    }

    void refresh() {
        auto linkStatus = Ethernet.linkStatus();
        if (linkStatus == LinkON) {
            if (isConnected) {
                return;
            } else {
                isConnected = true;
                _logger.logInfo("Ethernet cable has been connected");
            }
        }
        else if (linkStatus == LinkOFF && isConnected) {
            isConnected = false;
            _logger.logWarning("Ethernet cable has not been connected");
        }
    }
};