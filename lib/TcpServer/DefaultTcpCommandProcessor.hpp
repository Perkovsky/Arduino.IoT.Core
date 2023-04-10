#pragma once

#include <String.h>
#include "AbstractTcpCommandProcessor.hpp"

class DefaultTcpCommandProcessor final : public AbstractTcpCommandProcessor {
public:
    String getReply(const String& command) override {
        String reply("Reply: command '");
        reply += command;
        reply += "' has been received\r\n";
        return reply;
    }
};