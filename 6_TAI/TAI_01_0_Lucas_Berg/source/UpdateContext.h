#pragma once

namespace Tga
{
	class InputManager;
}

class GameWorld;

struct UpdateContext
{
	float myDeltaTime;
	const Tga::InputManager* myInputManager;
	GameWorld* myGameWold;
};

struct AIEvent
{
	enum class Type
	{
		ComputerActivated
	};

	Type myType;
	Tga::Vector2f myPosition;
};