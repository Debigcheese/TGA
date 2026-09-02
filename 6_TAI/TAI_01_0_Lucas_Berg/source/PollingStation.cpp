#include "PollingStation.h"

AI::PollingStation& AI::PollingStation::GetInstance()
{
    static PollingStation instance;
    return instance;
}

void AI::PollingStation::Init(Actor* player, Actor* aPCActor1, Actor* aPCActor2, Actor* aPCActor3)
{
    myPlayerActor = player;
    myPCActor1 = aPCActor1;
    myPCActor2 = aPCActor2;
    myPCActor3 = aPCActor3;
}

Tga::Vector2f AI::PollingStation::GetPlayerPosition() const
{
    if (myPlayerActor != nullptr)
    {
        return myPlayerActor->GetPosition();
    }

    return Tga::Vector2f();
}
