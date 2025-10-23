#pragma once
#include "GameStructs.h"

class SpellType
{
public:
	SpellType() : myAttributes({})
	{
	}

	void SetAttributes(const SpellAttributes& aAttributes) { myAttributes = aAttributes; }
	SpellAttributes GetSpellAttributes() const { return myAttributes; }

private:
	SpellAttributes myAttributes;
};
