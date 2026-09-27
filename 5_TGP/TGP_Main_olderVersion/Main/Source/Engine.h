#pragma once
#include <windows.h>
#include <memory>
#include "Graphics/GraphicsEngine.h"
#include "CommonUtilities/input/InputManager.h"
#include "CommonUtilities/Timer.h"

using namespace CommonUtilities;

// Configuration passed to Engine::Start
struct EngineConfiguration
{
	HINSTANCE hInstance = nullptr;
	int nCmdShow = SW_SHOW;
	int windowWidth = 1280;
	int windowHeight = 720;
	const wchar_t* windowTitle = L"Ooga booga Engine";
};

class Engine
{
public:
	Engine& operator=(const Engine&) = delete;
	Engine(const Engine&) = delete;

	static bool Start(const EngineConfiguration& aConfig = EngineConfiguration());
	static void Shutdown();
	static Engine* GetInstance() { return myInstance; }

	bool BeginFrame();  // returns false when the app should exit
	void EndFrame();

	GraphicsEngine& GetGraphicsEngine() const { return *myGraphicsEngine; }
	Tga::InputManager& GetInputManager()   const { return *myInputManager; }
	float GetDeltaTime() const { return myDeltaTime; }
	float GetTotalTime() const { return myTotalTime; }
	HWND GetHWND() const { return myHwnd; }

private:
	Engine() = default;
	~Engine() = default;

	bool InternalStart(const EngineConfiguration& aConfig);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static INT_PTR CALLBACK AboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	bool RegisterWindowClass(HINSTANCE hInstance, const wchar_t* aClassName);
	HWND CreateAppWindow(HINSTANCE hInstance, int nCmdShow, const wchar_t* aClassName, const wchar_t* aTitle, int aWidth, int aHeight);

	static Engine* myInstance;

	std::unique_ptr<GraphicsEngine> myGraphicsEngine;
	std::unique_ptr<Tga::InputManager> myInputManager;
	std::unique_ptr<Timer> myTimer;

	HWND myHwnd = nullptr;
	HINSTANCE myHInstance = nullptr;

	float myDeltaTime = 0.0f;
	float myTotalTime = 0.0f;

	bool myShouldExit = false;
};