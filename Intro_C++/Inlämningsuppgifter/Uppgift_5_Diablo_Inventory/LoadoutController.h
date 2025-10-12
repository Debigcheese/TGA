#pragma once

class Player;
class Room;

class LoadoutController
{
public:
    LoadoutController(Player& aPlayer);
    void UpdateLoadout(Room* aCurrentRoom);

    void UpdateEquipment() const;
    void UpdateInventory() const;
    void UpdateSpellBook() const;

    Player& GetPlayer() const { return myPlayer; }

private:
    Player& myPlayer;
    Room* myCurrentRoom;
};
