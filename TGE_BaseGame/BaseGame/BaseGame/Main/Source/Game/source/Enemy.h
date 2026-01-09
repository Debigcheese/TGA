//#pragma once
//#include "Entity.h"
//#include "tge/math/Vector2.h"
//#include "tge/Engine.h"
//#include "tge/drawers/SpriteDrawer.h"
//#include "tge/sprite/sprite.h"
//
//enum Side
//{
//	Left = 0,
//	Right = 1
//};
//
//enum class EnemyType
//{
//	Helicopter = 0,
//	Paratrooper = 1,
//	Jet = 2,
//	Bomb = 3
//};
//
//enum class LifeState
//{
//	Alive = 0,
//	Dead = 1,
//	Destroy = 2
//};
//
//class Enemy
//{
//	using DeathCallBack = std::function<void(Enemy*)>;
//
//public:
//	Enemy();
//	virtual ~Enemy();
//
//	virtual void Update(float aTimeDelta);
//	virtual void Render(Tga::SpriteDrawer& aSpriteDrawer);
//	void UpdateDeathAnimation(float aTimeDelta);
//
//	bool CheckOutOfBounds();
//
//	void SetOnDeath(DeathCallBack aCallBack) { myOnDeath = aCallBack; }
//	void OnDeath();
//	LifeState GetLifeState() const { return myLifeState; }
//
//	EnemyType GetType() const { return myType; }
//	Side GetSide() const { return mySide; }
//
//	//entity convenience wrappers
//	void SetPosition(Tga::Vector2f aPosition) { myEntity.SetPosition(aPosition); }
//	Tga::Vector2f GetPosition() const { return myEntity.GetPosition(); }
//	Tga::Vector2f GetSize() const { return myEntity.GetSize(); }
//
//protected:
//	Entity myEntity;
//
//	static constexpr int DEATH_TEXTURE_SIZE = 4;
//	Tga::TextureResource* myDeathTextures[DEATH_TEXTURE_SIZE];
//	float myDeathAnimTimer = 0;
//
//	DeathCallBack myOnDeath;
//
//	bool myIsAlive = true;
//	LifeState myLifeState = LifeState::Alive;
//	Side mySide;
//	EnemyType myType;
//};
