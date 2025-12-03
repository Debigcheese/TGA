#pragma once
#include "Weapon.h"

class Bow : public Weapon
{
public:
	Bow();
	~Bow();

	void SetRange(float aRange) { myRange = aRange; }

	void UpdateAnimation(float aTimeDelta);

private:
	static constexpr int TEXTURE_SIZE = 3;
	Tga::TextureResource* myTextures[TEXTURE_SIZE];
	float myAnimTimer;
};
