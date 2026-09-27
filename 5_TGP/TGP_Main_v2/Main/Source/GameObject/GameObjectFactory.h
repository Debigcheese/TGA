#pragma once
#include "GameObject.h"
#include "Model/Mesh.h"
#include <string>
#include <unordered_map>
#include <d3d11.h>

class GameObjectFactory
{
public:
	static GameObjectFactory& GetInstance();
	bool Init(ID3D11Device* aDevice);
	GameObject CreateGameObject(const std::string& aMeshName);
	bool LoadObj(ID3D11Device* aDevice, const std::string& aMeshName, const std::string& aFilePath);
private:
	GameObjectFactory() = default;

	std::unordered_map<std::string, Mesh> myMeshes;
	static GameObjectFactory* myInstance;

};