#pragma once
#include "GameStructs.h"

class ItemType
{
public:
	ItemType();
	void SetAttributes(const ItemAttributes& aAttributes);
	ItemAttributes GetAttributes() const;

	//ItemKey key;
	//ItemType type;
	//Rarity rarity;
	//const char* name;
	//float weight;
	//Attributes attributes;

private:
	ItemAttributes myAttributes;
};
