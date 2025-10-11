#pragma once
#include "WorldMap.h"
#include "Player.h"
#include "Room.h"
#include "CombatController.h"
#include "ScavengeController.h"

// EVERY WHILE LOOP + READ INPUT (MENU CHOICES) IS HANDLED IN THIS CLASS
class PlayerController
{
public:
    PlayerController(WorldMap& aWorldMap, Player& aPlayer);

    void UpdateAction();
    void UpdateNavigation();

    void UpdateInventory() const;
    void UpdateEquipment() const;
    void UpdateInventoryItems() const;
    void UpdateSpellBook() const;

    void UpdateAttributes() const;
    void Win() const;

private:
    Room* myCurrentRoom;
    WorldMap& myWorldMap;
    Player& myPlayer;
    CombatController myCombatController;
    ScavengeController myScavengeController;
};
