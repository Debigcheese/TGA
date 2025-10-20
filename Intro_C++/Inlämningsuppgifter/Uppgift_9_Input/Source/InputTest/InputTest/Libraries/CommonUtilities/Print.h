#pragma once
#include <iostream>
#include "InputHandler.h"
#include "InputTest.h"

using input = CommonUtilities::InputHandler;



namespace PrintInput
{
	void PrintLastKeyPressed(const input& inputHandler)
	{
		globalInputHandler
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

	void PrintMouseDelta(const input& inputHandler)
	{
		std::cout << "{" << inputHandler.GetMouseDelta().x << "x," << inputHandler.GetMouseDelta().y << "y}";
	}

	void PrintLMouseButton()
	{
		std::cout << IsLButtonDown();
	}

	void PrintRMouseButton()
	{
		std::cout << IsRButtonDown();
	}

	void PrintMMouseButton()
	{
		std::cout << IsMButtonDown();
	}
}
