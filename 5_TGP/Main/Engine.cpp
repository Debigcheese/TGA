#include "Engine.h"
//#include "Main.h"   // for IDI_MAIN, IDI_SMALL, IDC_MAIN, IDM_ABOUT, IDM_EXIT, IDD_ABOUTBOX
#include "Resource.h"
#include <cassert>
#include <iostream>

Engine* Engine::myInstance = nullptr;

// Public static interface
bool Engine::Start(const EngineConfiguration& aConfig)
{
	assert(myInstance == nullptr && "Engine::Start called more than once");
	myInstance = new Engine();
	if (!myInstance->InternalStart(aConfig))
	{
		delete myInstance;
		myInstance = nullptr;
		return false;
	}
	return true;
}

void Engine::Shutdown()
{
	delete myInstance;
	myInstance = nullptr;
}

// Frame control
bool Engine::BeginFrame()
{
	if (myShouldExit)
		return false;

	MSG msg = {};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
		{
			myShouldExit = true;
			return false;
		}
	}

	// Tick timer and input
	myTimer->Update();
	myInputManager->Update();

	myDeltaTime = myTimer->GetDeltaTime();
	myTotalTime += myDeltaTime;

	myGraphicsEngine->BeginFrame();
	return true;
}

void Engine::EndFrame()
{
	myGraphicsEngine->EndFrame();
}

// Internal startup
bool Engine::InternalStart(const EngineConfiguration& aConfig)
{
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);

	myHInstance = aConfig.hInstance;

	static const wchar_t* className = aConfig.windowTitle;

	if (!RegisterWindowClass(aConfig.hInstance, className))
		return false;

	myHwnd = CreateAppWindow(
		aConfig.hInstance,
		aConfig.nCmdShow,
		className,
		aConfig.windowTitle,
		aConfig.windowWidth,
		aConfig.windowHeight
	);

	if (!myHwnd)
		return false;

	// Graphics engine
	myGraphicsEngine = std::make_unique<GraphicsEngine>();
	if (!myGraphicsEngine->Init(myHwnd, {}))
		return false;

	// Input manager
	myInputManager = std::make_unique<Tga::InputManager>(myHwnd);

	// Timer
	myTimer = std::make_unique<Timer>();
	myTimer->Update();

	return true;
}

// Window creation helpers
bool Engine::RegisterWindowClass(HINSTANCE hInstance, const wchar_t* aClassName)
{
	WNDCLASSEXW wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = aClassName;
	wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassExW(&wcex) != 0;
}

HWND Engine::CreateAppWindow(HINSTANCE hInstance, int nCmdShow, const wchar_t* aClassName, const wchar_t* aTitle, int aWidth, int aHeight)
{
	RECT rect = { 0, 0, aWidth, aHeight };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hWnd = CreateWindowW(
		aClassName, aTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		nullptr, nullptr, hInstance, nullptr
	);

	if (!hWnd)
		return nullptr;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return hWnd;
}

LRESULT CALLBACK Engine::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Forward to input manager before any other handling
	if (myInstance && myInstance->myInputManager)
		myInstance->myInputManager->UpdateEvents(message, wParam, lParam);

	switch (message)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDM_ABOUT:
			DialogBox(myInstance->myHInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AboutProc);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK Engine::AboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}