#include "GameObjectFactory.h"
#include "Model/PrimitiveMeshes.h"
#include "../Shader/ShaderFactory.h"

GameObjectFactory* GameObjectFactory::myInstance = nullptr;

GameObjectFactory& GameObjectFactory::GetInstance()
{
	static GameObjectFactory instance;
	return instance;
}

bool GameObjectFactory::Init(ID3D11Device* aDevice)
{
	auto& shaders = ShaderFactory::GetInstance();

	myMeshes["Cube"].Init(aDevice,
		Primitives::CubeVertices, 8,
		Primitives::CubeIndices, 36,
		shaders.GetShader("colored"));

	myMeshes["Pyramid"].Init(aDevice,
		Primitives::PyramidVertices, 5,
		Primitives::PyramidIndices, 18,
		shaders.GetShader("animated"));

	return true;
}

GameObject GameObjectFactory::CreateGameObject(const std::string& aMeshName)
{
	GameObject obj;
	auto it = myMeshes.find(aMeshName);
	if (it != myMeshes.end())
		obj.SetMesh(&it->second);
	return obj;
}