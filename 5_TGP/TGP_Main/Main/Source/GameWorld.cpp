#include "GameWorld.h"
#include "Engine.h"
#include <cassert>

#include "Shader/ShaderFactory.h"

#include "TGAFBXImporter/source/Importer.h"

#include "CommonUtilities/input/InputManager.h"

GameWorld::~GameWorld()
{
	TGA::FBX::Importer::UninitImporter();
}

bool GameWorld::Init()
{
	TGA::FBX::Importer::InitImporter();
	auto& engine = *Engine::GetInstance();
	auto& ge = engine.GetGraphicsEngine();
	auto device = ge.GetDevice();
	auto context = ge.GetContext();
	assert(device && "device null");
	assert(context && "context null");

	if (!myCamera.Initialize(90.0f, {(float)ge.GetWidth(), (float)ge.GetHeight()}, 0.1f, 1000.0f))
		return false;

	myCamera.SetPosition({0.0f, FLOOR_HEIGHT + 7.0f, -34.0f});
	myCameraController.Initialize(&myCamera, &engine.GetInputManager());

	if (!ShaderFactory::GetInstance().Init(device))
		return false;

	if (!GameObjectFactory::GetInstance().Init(device, context))
		return false;

	if (!myRenderer.Init())
		return false;

	if (!myScene.Init())
		return false;

	return true;
}

void GameWorld::Update(float aDeltaTime)
{
	myTotalTime += aDeltaTime;
	myCameraController.Update(aDeltaTime);

	myScene.Update(myTotalTime);
}

void GameWorld::Render()
{
	myRenderer.Render(myScene, myCamera, myTotalTime);
}
