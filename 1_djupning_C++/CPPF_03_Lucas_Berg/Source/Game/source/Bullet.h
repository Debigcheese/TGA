#pragma once
#include "tge/math/Vector2.h"
#include "tge/math/Vector2.h"
#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
#include "tge/sprite/sprite.h"

class Bullet
{
public:
	Bullet();
	~Bullet();

	void Update(float aTimeDelta);
	void Render(Tga::SpriteDrawer& aSpriteDrawer);

	void SetPosition(Tga::Vector2f aPosition) { mySpriteInstance.myPosition = aPosition; }
	void SetDirection(Tga::Vector2f aDirection) { myDirection = aDirection; }
	void SetRotation(float aRotation) { mySpriteInstance.myRotation = aRotation; }

	Tga::Vector2f GetPosition() const { return mySpriteInstance.myPosition; }
	Tga::Vector2f GetSize() const { return mySpriteInstance.mySize; }

	bool GetOutOfBounds() const { return myOutOfBounds; }

private:
	void CheckOutOfBounds();

	Tga::Sprite2DInstanceData mySpriteInstance;
	Tga::SpriteSharedData mySpriteData;

	Tga::Vector2f myResolution;
	Tga::Vector2f myDirection;
	float mySpeed = 600.0f;
	bool myOutOfBounds = false;
};
