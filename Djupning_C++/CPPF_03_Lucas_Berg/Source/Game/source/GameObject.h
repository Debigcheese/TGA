#pragma once
#include "tge/math/Vector2.h"
#include "tge/sprite/sprite.h"

struct MovementData
{
	Tga::Vector2f direction;
	Tga::Vector2f velocity;
	Tga::Vector2f speed;
	float gravity;
};

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Update(float aTimeDelta);

	void SetSpriteInstance(const Tga::Sprite2DInstanceData& aSpriteInstance) { mySpriteInstance = aSpriteInstance; }
	Tga::Sprite2DInstanceData GetSpriteInstance() const { return mySpriteInstance; }

	void SetSpriteSharedData(const Tga::SpriteSharedData& aSpriteData) { mySpriteData = aSpriteData; }
	Tga::SpriteSharedData GetSpriteSharedData() const { return mySpriteData; }

	void SetMovement(const MovementData& aMovement) { myMovement = aMovement; }
	MovementData GetMovement() const { return myMovement; }

private:
	Tga::Sprite2DInstanceData mySpriteInstance;
	Tga::SpriteSharedData mySpriteData;
	MovementData myMovement;

	Tga::Vector2f myResolution;
};
