#pragma once
#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
#include "Helicopter.h"
#include "CommonUtilities/InputHandler.h"
#include "SharedTypes.h"

using Input = CommonUtilities::InputHandler;

class Player
{
public:
	Player();
	~Player();

	void Init(Tga::Engine& aEngine);
	void CheckInit();
	void Update(float aTimeDelta);
	void Render(Tga::SpriteDrawer& aSpriteDrawer);
	void Possess(Helicopter* aHelicopter);

	Input* GetInput() const { return myInputHandler; }
	Helicopter* GetHelicopter() const { return myHelicopter; }
	Actor GetActor() const { return Actor::Player; }

private:
	Input* myInputHandler;
	Helicopter* myHelicopter;

	Tga::Vector2f myScreenResolution;
};
