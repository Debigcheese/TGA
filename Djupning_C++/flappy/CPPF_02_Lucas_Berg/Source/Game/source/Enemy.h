#pragma once
#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
#include "Paddle.h"
#include "CommonUtilities/Timer.h"
#include "Ball.h"
#include "Config.h"

using Timer = CommonUtilities::Timer;

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init(Tga::Engine& aEngine, Ball* aBall);
	void Update(float aTimeDelta);
	void Render(Tga::SpriteDrawer& aSpriteDrawer);

	Tga::Vector2f GetDirectionTo(Ball* aBall);
	Tga::Vector2f GetRandomDirection();

	void SetTargetBall(Ball* aBall);
	Paddle* GetPaddle();
	Actor GetActor() const;

private:
	Paddle* myPaddle;
	Ball* myTargetBall;
	Timer* myTimer;

	float myDirectionTimer;
	float myChaseAfterHitTimer;
	bool myUsingRandomDirection;

	Tga::Vector2f myScreenResolution;
};
