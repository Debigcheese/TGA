#pragma once
#include "GameStructs.h"

class EnemyType
{
public:
	EnemyType() : myAttributes({})
	{
	}

	void SetAttributes(const EnemyAttributes& aAttributes) { myAttributes = aAttributes; }
	EnemyAttributes GetAttributes() const { return myAttributes; }

	//ItemKey key;
	//ItemType type;
	//Rarity rarity;
	//const char* name;
	//float weight;
	//Attributes attributes;

private:
	EnemyAttributes myAttributes;
};
