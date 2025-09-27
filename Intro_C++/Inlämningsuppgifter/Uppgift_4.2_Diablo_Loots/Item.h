#pragma once
#include "GameStructs.h"
#include "GameEnums.h"
#include <vector>

class Player;

class Item
{
public:
	Item(int aId);

	void SetId(int aNewId);
	void PrintItemOnPickup() const;
	void PrintItemAttributes() const;

private:
	ItemAttributes myAttributes;
};
