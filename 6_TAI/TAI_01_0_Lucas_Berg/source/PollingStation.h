#pragma once

#include "Actor.h"
#include <vector>

namespace AI
{
    class PollingStation
    {
    public:
        static PollingStation& GetInstance();

        void Init(Actor* player, Actor* aPCActor1, Actor* aPCActor2, Actor* aPCActor3 );

        Tga::Vector2f GetPlayerPosition() const;
        Tga::Vector2f GetPC1Position() const { return myPCActor1->GetPosition(); }
        Tga::Vector2f GetPC2Position() const { return myPCActor2->GetPosition(); }
        Tga::Vector2f GetPC3Position() const { return myPCActor3->GetPosition(); }

        // Vi sätter boolen till true i gameworld, polling enemies checkar bool värdet. 
        void SetPlayerOnComputer(PlayerOnPC aValue){ myPlayerOnComputer = aValue;}
        PlayerOnPC isPlayerOnComputer() { return myPlayerOnComputer;}

        ~PollingStation() = default;

    private:
        PollingStation() = default;

        PollingStation(const PollingStation&) = delete;
        PollingStation& operator=(const PollingStation&) = delete;

        PlayerOnPC myPlayerOnComputer;
        Actor* myPlayerActor = nullptr;
        Actor* myPCActor1 = nullptr;
        Actor* myPCActor2= nullptr;
        Actor* myPCActor3 = nullptr;

    };
}
