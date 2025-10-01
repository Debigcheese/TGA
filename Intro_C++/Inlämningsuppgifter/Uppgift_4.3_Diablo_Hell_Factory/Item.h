#pragma once
#include "GameStructs.h"
#include "ItemType.h"

class Player;

class Item
{
public:
	Item(ItemType* myItemType);

	//const char* GetName() const;
	//float GetWeight() const;
	//ItemAttributes GetAttributes() const;

	void PrintItemAttributes() const;
	void PrintItemOnPickup() const;
	void PrintItemOnDisplay() const;
	void PrintItemName() const;

private:
	ItemType* myItemType;
};
