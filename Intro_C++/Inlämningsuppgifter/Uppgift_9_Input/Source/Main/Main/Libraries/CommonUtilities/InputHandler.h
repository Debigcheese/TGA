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
		                 myMousePos(), myPreviousMousePos(), myMouseDelta()
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
						myMousePos.x = GET_X_LPARAM(lParam);
						myMousePos.y = GET_Y_LPARAM(lParam);

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
				case WM_MOUSEWHEEL:
					{
						myWheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
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
			return myMousePos;
		}

		void SetMousePosition(const POINT aPoint) const
		{
			SetCursorPos(aPoint.x, aPoint.y);
		}

		POINT GetMouseAbsolutePOS() const
		{
			POINT pos;
			GetCursorPos(&pos);
			return pos;
		}

		POINT GetMouseDelta() const
		{
			return myMouseDelta;
		}

		void UpdateMouseDelta()
		{
			myMouseDelta.x = myMousePos.x - myPreviousMousePos.x;
			myMouseDelta.y = myMousePos.y - myPreviousMousePos.y;
		}

		short GetWheelDelta() const
		{
			return myWheelDelta;
		}

		bool UpdateMouseInput(UINT aMessage)
		{
			//
		}

		void LockMouseToWindow(HWND hWnd)
		{
			RECT rc;
			GetClientRect(hWnd, &rc);
			POINT tl{rc.left, rc.top};
			POINT br{rc.right, rc.bottom};

			ClientToScreen(hWnd, &tl);
			ClientToScreen(hWnd, &br);
			RECT clip{tl.x, tl.y, br.x, br.y};

			ClipCursor(&clip);
			SetCapture(hWnd);
			ShowCursor(FALSE);
		}

		void UnlockFromWindow()
		{
			ClipCursor(nullptr);
			ReleaseCapture();
			ShowCursor(TRUE);
		}

		void UpdateInput()
		{
			UpdateMouseDelta();
			myPreviousMousePos = myMousePos;

			myPreviousState = myCurrentState;
			myWheelDelta = 0;
		}

	private:
		std::array<bool, 256> myCurrentState = {false};
		std::array<bool, 256> myPreviousState = {false};
		std::array<bool, 256> myInputState = {false};

		POINT myMousePos = {0, 0};
		POINT myPreviousMousePos = {0, 0};

		POINT myAbsoluteMousePos = {0, 0};
		POINT myPreviousAbsoluteMousePos = {0, 0};

		POINT myMouseDelta = {0, 0};
		short myWheelDelta = 0;

		int myLastKeyUp = 0;
		int myLastKeyDown = 0;
	};
}

extern CommonUtilities::InputHandler globalInputHandler;
