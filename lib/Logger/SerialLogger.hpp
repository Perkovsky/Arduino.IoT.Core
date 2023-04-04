#pragma once

#include <String.h>
#include <Arduino.h>
#include "BaseLogger.hpp"

class SerialLogger final : public BaseLogger {
private:
    Stream& _stream;

public:
    SerialLogger(const LogLevel logLevel, Stream& stream, uRTCLib* rtc = nullptr)
        : BaseLogger(logLevel, rtc), _stream(stream) {}

protected:
    bool log(const String& message) override {
        _stream.println(message);
        return true;
    }
};