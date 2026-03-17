#pragma once
#include <vector>

class IMessageListener;

class Message
{
public:
    virtual ~Message() {}
};

class MessageBus
{
public:
    static MessageBus* GetInstance();

    void Subscribe(IMessageListener* listener);

    void Publish(Message* msg) const;

private:
    MessageBus() {}
    static MessageBus* myInstance;
    std::vector<IMessageListener*> myListeners;
};
