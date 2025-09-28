#pragma once
#include "GameStructs.h"
#include "GameEnums.h"
#include <vector>

class Player;

class Item
{
public:
	Item(int aId);

	const char* GetName() const;
	float GetWeight() const;
	ItemAttributes GetAttributes() const;

	void SetId(int aNewId);
	void PrintItemAttributes() const;
	void PrintItemOnPickup() const;
	void PrintItemOnDisplay() const;
	void PrintItemName() const;

private:
	ItemAttributes myAttributes;
};
