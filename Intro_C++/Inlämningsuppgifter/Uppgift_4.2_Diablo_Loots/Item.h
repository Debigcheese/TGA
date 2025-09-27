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
	void PrintItemOnPickup() const;
	void PrintItemAttributes() const;

private:
	ItemAttributes myAttributes;
};
