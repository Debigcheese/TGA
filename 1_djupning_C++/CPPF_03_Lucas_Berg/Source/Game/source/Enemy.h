#pragma once
#include "tge/math/Vector2.h"
#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
#include "tge/sprite/sprite.h"


enum Side
{
	Left = 0,
	Right = 1
};

enum class EnemyType
{
	Helicopter = 0,
	Paratrooper = 1,
	Jet = 2,
	Bomb = 3
};

enum class LifeState
{
	Alive = 0,
	Dead = 1,
	Destroy = 2
};

class Enemy
{
	using DeathCallBack = std::function<void(Enemy*)>;

public:
	Enemy();
	virtual ~Enemy();

	virtual void Update(float aTimeDelta);
	virtual void Render(Tga::SpriteDrawer& aSpriteDrawer);
	void UpdateDeathAnimation(float aTimeDelta);

	bool CheckOutOfBounds();

	void SetOnDeath(DeathCallBack aCallBack) { myOnDeath = aCallBack; }
	void OnDeath();
	LifeState GetLifeState() const { return myLifeState; }

	void SetPosition(Tga::Vector2f aPosition) { mySpriteInstance.myPosition = aPosition; }
	Tga::Vector2f GetPosition() const { return mySpriteInstance.myPosition; }
	Tga::Vector2f GetSize() const { return mySpriteInstance.mySize; }
	EnemyType GetType() const { return myType; }
	Side GetSide() const { return mySide; }

protected:
	Tga::Vector2f myResolution;

	Tga::Sprite2DInstanceData mySpriteInstance;
	Tga::SpriteSharedData mySpriteData;

	static constexpr int TEXTURE_SIZE = 4;
	Tga::TextureResource* myTextures[TEXTURE_SIZE];
	float myAnimTimer = 0;

	Tga::Vector2f myDirection;
	float mySpeed = 100.0f;

	DeathCallBack myOnDeath;

	bool myIsAlive = true;
	LifeState myLifeState = LifeState::Alive;
	Side mySide;
	EnemyType myType;
};
