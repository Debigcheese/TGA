#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <array>

namespace CommonUtilities
{
	class InputHandler
	{
	public:
		InputHandler() : myCurrentState(), myPreviousState(), myInputState(),
		                 myCurrentMousePos(), myPreviousMousePos(), myMouseDelta()
		{
		}

		bool UpdateEvents(UINT aMessage, WPARAM wParam, LPARAM lParam)
		{
			switch (aMessage)
			{
				case WM_KEYDOWN:
				{
					myCurrentState[wParam] = true;
					myLastKeyDown = static_cast<int>(wParam);
					return true;
				}
				case WM_KEYUP:
				{
					myCurrentState[wParam] = false;
					myLastKeyUp = static_cast<int>(wParam);
					return true;
				}
				case WM_MOUSEMOVE:
				{
					myCurrentMousePos.x = GET_X_LPARAM(lParam);
					myCurrentMousePos.y = GET_Y_LPARAM(lParam);
					return true;
				}
				case WM_LBUTTONDOWN:
				{
					myCurrentState[VK_LBUTTON] = true;
					return true;
				}

				case WM_LBUTTONUP:
				{
					myCurrentState[VK_LBUTTON] = false;
					return true;
				}

				case WM_RBUTTONDOWN:
				{
					myCurrentState[VK_RBUTTON] = true;
					return true;
				}

				case WM_RBUTTONUP:
				{
					myCurrentState[VK_RBUTTON] = false;
					return true;
				}

				case WM_MBUTTONDOWN:
				{
					myCurrentState[VK_MBUTTON] = true;
					return true;
				}

				case WM_MBUTTONUP:
				{
					myCurrentState[VK_MBUTTON] = false;
					return true;
				}
			}
			return false;
		}

		bool IsKeyDown(const int aKeyKode) const
		{
			return myCurrentState[aKeyKode];
		}

		bool IsKeyPressed(const int aKeyCode) const
		{
			return myCurrentState[aKeyCode] && !myPreviousState[aKeyCode];
		}

		bool IsKeyReleased(const int aKeyCode) const
		{
			return !myCurrentState[aKeyCode] && myPreviousState[aKeyCode];
		}

		int GetLastKeyPressed() const
		{
			return myLastKeyDown;
		}

		int GetLastKeyReleased() const
		{
			return myLastKeyUp;
		}

		POINT GetMousePosition() const
		{
			return myCurrentMousePos;
		}

		POINT GetMouseDelta() const
		{
			return myMouseDelta;
		}

		bool UpdateMouseInput(UINT aMessage)
		{
		}

		void UpdateInput()
		{
			myMouseDelta.x = myCurrentMousePos.x - myPreviousMousePos.x;
			myMouseDelta.y = myCurrentMousePos.y - myPreviousMousePos.y;
			myPreviousMousePos = myCurrentMousePos;

			myPreviousState = myCurrentState;
		}

	private:
		std::array<bool, 256> myCurrentState = {false};
		std::array<bool, 256> myPreviousState = {false};
		std::array<bool, 256> myInputState = {false};

		POINT myCurrentMousePos = {0, 0};
		POINT myPreviousMousePos = {0, 0};
		POINT myMouseDelta = {0, 0};

		int myLastKeyUp = 0;
		int myLastKeyDown = 0;
	};
}
