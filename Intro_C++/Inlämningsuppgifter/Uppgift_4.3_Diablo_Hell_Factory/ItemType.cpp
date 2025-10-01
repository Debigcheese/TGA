#include "ItemType.h"

ItemType::ItemType()
	: myAttributes({})
{
}

void ItemType::SetAttributes(const ItemAttributes& aAttributes)
{
	myAttributes = aAttributes;
}

ItemAttributes ItemType::GetAttributes() const
{
	return myAttributes;
}
