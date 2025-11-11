#include "Enemy.h"
#include "Ball.h"
#include "CommonUtilities/Random.h"

Enemy::Enemy()
{
	myScreenResolution = {1920.0f, 1080.0f};
	myUsingRandomDirection = false;
}

Enemy::~Enemy()
{
}

void Enemy::Init(Tga::Engine& aEngine, Ball* aBall)
{
	//Get resolution
	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};

	myPaddle = new Paddle();
	myPaddle->Init(aEngine, GetActor());
	myPaddle->SetPosition({myScreenResolution.x - 50, myScreenResolution.y + 200});

	myTimer = new Timer();
	myTimer->Start();
	SetTargetBall(aBall);
}

void Enemy::Update(float aTimeDelta)
{
	myTimer->Update();
	myChaseAfterHitTimer += myTimer->GetDeltaTime();

	Paddle* paddle = GetPaddle();

	if (myChaseAfterHitTimer < 0.75f && myTargetBall->GetDirection().x < 0.0f)
	{
		paddle->SetDirection(GetDirectionTo(myTargetBall));
		myPaddle->Update(aTimeDelta);
		return;
	}

	if (myTargetBall->GetDirection().x < 0.0f)
	{
		paddle->SetDirection({0.0f, 0.0f});
		myPaddle->Update(aTimeDelta);
		return;
	}

	myDirectionTimer += myTimer->GetDeltaTime();

	if (!myUsingRandomDirection)
	{
		paddle->SetDirection(GetDirectionTo(myTargetBall));
	}
	if (myDirectionTimer < 2.0f && myDirectionTimer >= 1.5f)
	{
		paddle->SetDirection(GetRandomDirection());
	}
	if (myDirectionTimer >= 2.0f)
	{
		myDirectionTimer = 0;
		myUsingRandomDirection = false;
	}
	myChaseAfterHitTimer = 0.0f;
	myPaddle->Update(aTimeDelta);
}

void Enemy::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	myPaddle->Render(aSpriteDrawer);
}

Tga::Vector2f Enemy::GetDirectionTo(Ball* aBall)
{
	if (myPaddle->GetPosition().y - aBall->GetPosition().y > 0)
	{
		return {0.0f, -1.0f};
	}
	if (myPaddle->GetPosition().y - aBall->GetPosition().y < 0)
	{
		return {0.0f, 1.0f};
	}
	return {0.0f, 0.0f};
}

Tga::Vector2f Enemy::GetRandomDirection()
{
	if (myUsingRandomDirection)
	{
		return myPaddle->GetDirection();
	}

	myUsingRandomDirection = true;

	int random = globalRNG.RangeInt(1, 2);
	if (random <= 1)
	{
		return {0.0f, -1.0f};
	}
	return {0.0f, 1.0f};
}

void Enemy::SetTargetBall(Ball* aBall)
{
	myTargetBall = aBall;
}

Paddle* Enemy::GetPaddle()
{
	return myPaddle;
}

Actor Enemy::GetActor() const
{
	return Actor::Enemy;
}
