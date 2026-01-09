#pragma once
#include "GameStructs.h"

class ItemType
{
public:
	ItemType() : myAttributes({})
	{
	}

	void SetAttributes(const ItemAttributes& aAttributes) { myAttributes = aAttributes; }
	ItemAttributes GetItemAttributes() const { return myAttributes; }

private:
	ItemAttributes myAttributes;
};
