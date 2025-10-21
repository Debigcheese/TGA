#include "pch.h"
#include "InputTest.h"

namespace InputTest
{
	input* myInputHandler = nullptr;
	HWND myMainWindowHandle = nullptr;
	bool myMouseLocked = false;

	POINT GetClientCenterScreenSpace(HWND aHwnd)
	{
		RECT rc{};
		GetClientRect(aHwnd, &rc);
		POINT tl{rc.left, rc.top};
		POINT br{rc.right, rc.bottom};
		ClientToScreen(aHwnd, &tl);
		ClientToScreen(aHwnd, &br);
		POINT center{
			tl.x + (br.x - tl.x) / 2,
			tl.y + (br.y - tl.y) / 2
		};
		return center;
	}

	void PrintInstructions()
	{
		std::cout <<
			"=== Input Test Controls ===\n"
			"[Tangent]  SPACE: KeyPressed-test\n"
			"[Tangent]  LSHIFT: KeyDown/held-test\n"
			"[Tangent]  LCTRL: KeyReleased-test\n"
			"[Mus]      L/R/M-knapp: Down/Pressed/Released\n"
			"[Mus]      Rör musen: pos/delta\n"
			"[Hjul]     Scrolla: wheel-delta\n"
			"[Extra]    M: set mouse pos till mitten\n"
			"[Extra]    C: capture/lock mouse\n"
			"[Extra]    U: unlock mouse\n"
			"[Exit]     ESC: avsluta\n"
			"===========================\n\n";
	}

	void RunTests()
	{
		auto& inputRef = *myInputHandler;

		// === Tangenter ===
		if (inputRef.IsKeyPressed(VK_SPACE))
			std::cout << "[KeyPressed] SPACE\n";

		if (inputRef.IsKeyDown(VK_LSHIFT))
			std::cout << "[KeyDown] LSHIFT\n";

		if (inputRef.IsKeyReleased(VK_LCONTROL))
			std::cout << "[KeyReleased] LCTRL\n";

		// === Musknappar ===
		if (inputRef.IsKeyPressed(VK_LBUTTON)) std::cout << "[Pressed] LMB\n";
		if (inputRef.IsKeyPressed(VK_RBUTTON)) std::cout << "[Pressed] RMB\n";
		if (inputRef.IsKeyPressed(VK_MBUTTON)) std::cout << "[Pressed] MMB\n";

		if (inputRef.IsKeyReleased(VK_LBUTTON)) std::cout << "[Released] LMB\n";
		if (inputRef.IsKeyReleased(VK_RBUTTON)) std::cout << "[Released] RMB\n";
		if (inputRef.IsKeyReleased(VK_MBUTTON)) std::cout << "[Released] MMB\n";

		if (inputRef.IsKeyDown(VK_LBUTTON)) std::cout << "[Down] LMB\n";
		if (inputRef.IsKeyDown(VK_RBUTTON)) std::cout << "[Down] RMB\n";
		if (inputRef.IsKeyDown(VK_MBUTTON)) std::cout << "[Down] MMB\n";

		// === Musrörelse ===
		if (inputRef.GetMouseDelta().x != 0 || inputRef.GetMouseDelta().y != 0)
		{
			std::cout << "[MousePos] ";
			PrintInput::PrintMousePOS();
			std::cout << " [Delta] ";
			PrintInput::PrintMouseDelta();
			std::cout << "\n";
		}

		// === Hjul ===
		if (inputRef.GetWheelDelta() != 0)
			std::cout << "[Wheel] delta=" << inputRef.GetWheelDelta() << "\n";

		// === Extra ===
		if (inputRef.IsKeyPressed('M'))
		{
			POINT center = GetClientCenterScreenSpace(myMainWindowHandle);
			inputRef.SetMousePosition(center);
			std::cout << "[SetMousePosition] center (" << center.x << "," << center.y << ")\n";
		}

		if (inputRef.IsKeyPressed('C'))
		{
			if (!myMouseLocked)
			{
				inputRef.LockMouseToWindow(myMainWindowHandle);
				myMouseLocked = true;
				std::cout << "[Capture] locked to window\n";
			}
			else
			{
				inputRef.UnlockFromWindow();
				myMouseLocked = false;
				std::cout << "[Capture] unlocked\n";
			}
		}

		if (inputRef.IsKeyPressed('U'))
		{
			inputRef.UnlockFromWindow();
			myMouseLocked = false;
			std::cout << "[Capture] unlocked (U)\n";
		}

		if (inputRef.IsKeyPressed(VK_ESCAPE))
		{
			PostQuitMessage(0);
		}
	}
}
