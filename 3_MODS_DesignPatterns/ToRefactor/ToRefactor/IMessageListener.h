#pragma once

class Message;

class IMessageListener
{
public:
    virtual ~IMessageListener() {}
    virtual void HandleMessage(Message* msg) = 0;
};
