#pragma once

#include <Arduino.h>
#include "AbstractDateTimeProvider.hpp"

class DefaultDateTimeProvider final : public AbstractDateTimeProvider {
public:
    String getTimestamp() override {
        return String(millis());
    }
};