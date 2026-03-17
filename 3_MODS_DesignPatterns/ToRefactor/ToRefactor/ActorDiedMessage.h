#pragma once
#include "MessageBus.h"

class Actor;

class ActorDiedMessage : public Message
{
public:
    Actor* myVictim;
    Actor* myKiller;
    ActorDiedMessage(Actor* victim, Actor* killer) : myVictim(victim), myKiller(killer) {}
};