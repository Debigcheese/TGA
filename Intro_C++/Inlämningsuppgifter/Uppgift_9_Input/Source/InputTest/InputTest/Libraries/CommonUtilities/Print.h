#pragma once
#include <iostream>
#include "InputHandler.h"

using input = CommonUtilities::InputHandler;

namespace Print
{
	void PrintLastKeyPressed(const input& inputHandler)
	{
		if (inputHandler.IsKeyPressed(inputHandler.GetLastKeyPressed()))
		{
			std::cout << static_cast<char>(inputHandler.GetLastKeyPressed());
		}
	}

	void PrintLastKeyReleased(const input& inputHandler)
	{
		if (inputHandler.IsKeyReleased(inputHandler.GetLastKeyReleased()))
		{
			std::cout << static_cast<char>(inputHandler.GetLastKeyReleased());
		}
	}

	void PrintLastKeyDown(const input& inputHandler)
	{
		if (inputHandler.IsKeyDown(inputHandler.GetLastKeyPressed()))
		{
			std::cout << static_cast<char>(inputHandler.GetLastKeyPressed());
		}
	}

	void PrintMousePOS(const input& inputHandler)
	{
		if (inputHandler.GetMouseDelta().x != 0 || inputHandler.GetMouseDelta().y != 0)
		{
			std::cout << "{" << inputHandler.GetMousePosition().x << "x," << inputHandler.GetMousePosition().y << "y}";
		}
	}
}
