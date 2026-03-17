#pragma once
#include <string>

#include "MessageBus.h"

class Log_Message : public Message
{
public:
    std::string text;
    Log_Message(std::string text) : text(text) {}
};

