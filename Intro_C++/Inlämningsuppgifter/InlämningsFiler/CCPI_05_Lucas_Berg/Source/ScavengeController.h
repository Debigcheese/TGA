#pragma once
#include "Player.h"

class ScavengeController
{
public:
    ScavengeController(Player& aPlayer);

    void UpdateScavenge(Room* aCurrentRoom);
    void UpdatePickupItem() const;
    void UpdateLootChests() const;
    void UpdateReadSpells() const;

private:
    Player& myPlayer;
    Room* myCurrentRoom;
};
