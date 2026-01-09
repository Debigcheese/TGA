#pragma once
#include "GameStructs.h"

class ItemType
{
public:
    ItemType() : myItemAttributes({})
    {
    }

    void SetItemAttributes(const ItemAttributes& aAttributes) { myItemAttributes = aAttributes; }
    const ItemAttributes& GetItemAttributes() const { return myItemAttributes; }

private:
    ItemAttributes myItemAttributes;
};
