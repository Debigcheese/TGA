#pragma once
#include "Camera/Camera.h"
#include "Camera/CameraController.h"
#include "Graphics/GraphicsRenderer.h"
#include "Scene.h"

namespace Tga
{
	class InputManager;
}

class GameWorld
{
public:
	GameWorld() = default;
	~GameWorld();

	bool Init();
	void Update(float aDeltaTime);
	void Render();

private:
	Camera myCamera;
	CameraController myCameraController;

	Scene myScene;
	GraphicsRenderer myRenderer;

	float myTotalTime = 0.0f;
};
