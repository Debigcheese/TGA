#include "MessageBus.h"

#include "IMessageListener.h"

MessageBus* MessageBus::myInstance = nullptr;

MessageBus* MessageBus::GetInstance()
{
    if (!myInstance)
    {
        myInstance = new MessageBus();
    }
    return myInstance;
}

void MessageBus::Subscribe(IMessageListener* listener)
{
    myListeners.push_back(listener);
}

void MessageBus::Publish(Message* msg) const
{
    for (IMessageListener* listener : myListeners)
    {
        listener->HandleMessage(msg);
    }
    delete msg;
}
