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
    static constexpr int RETURN_INDEX_OFFSET = 1;

    Player& myPlayer;
    Room* myCurrentRoom;
};
