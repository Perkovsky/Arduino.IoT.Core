#pragma once

#include <String.h>

class AbstractTcpCommandProcessor {
protected:
    virtual ~AbstractTcpCommandProcessor() = default;

public:
   virtual String getReply(const String& command) = 0;
};