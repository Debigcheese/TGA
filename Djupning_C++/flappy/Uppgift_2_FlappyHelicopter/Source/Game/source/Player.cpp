#include "Player.h"

Player::Player()
{
	myScreenResolution = {1920.0f, 1080.0f};
}

Player::~Player()
{
}

void Player::Init(Tga::Engine& aEngine)
{
	//Get resolution
	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};

	myInputHandler = &globalInputHandler;
}

void Player::CheckInit()
{
	if (!myInputHandler)
	{
		std::cout << "Player has no input handler!" << std::endl;
		return;
	}
	if (!myHelicopter)
	{
		std::cout << "Player has no helicopter possessed!" << std::endl;
		return;
	}
}

void Player::Update(float aTimeDelta)
{
	CheckInit();

	if (myInputHandler->IsKeyDown(KEY_SPACE) && !myHelicopter->GetJumpData().isJumping)
	{
		myHelicopter->SetDirection({0, 1});
	}
	else
	{
		myHelicopter->SetDirection({0, -1});
	}

	myHelicopter->Update(aTimeDelta);

	myInputHandler->UpdateInput();
}

void Player::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	myHelicopter->Render(aSpriteDrawer);
}

void Player::Possess(Helicopter* aHelicopter)
{
	myHelicopter = aHelicopter;
}
