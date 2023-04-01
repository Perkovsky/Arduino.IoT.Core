#pragma once

#include <String.h>
#include <Arduino.h>
#include "BaseLogger.hpp"

class SerialLogger final : public BaseLogger {
private:
    const Stream& _stream;

public:
    SerialLogger(const LogLevel logLevel, const Stream& stream, uRTCLib* rtc = nullptr)
        : BaseLogger(logLevel, rtc), _stream(stream) {}

protected:
    void log(const String& message) override {
        _stream.println(message);
    }
};