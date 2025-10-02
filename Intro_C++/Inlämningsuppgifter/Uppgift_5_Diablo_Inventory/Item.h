#pragma once
#include "GameStructs.h"
#include "ItemType.h"

class Player;

class Item
{
public:
	Item(ItemType* aItemType);

	ItemAttributes GetItemAttributes() const { return myItemType->GetItemAttributes(); }
	Attributes GetAttributes() const { return GetItemAttributes().attributes; }

	void PrintItemAttributes() const;
	void PrintItemOnPickup() const;
	void PrintItemOnDisplay() const;
	void PrintItemName() const;

private:
	ItemType* myItemType;
};
