#pragma once
#include "GameObject.h"
#include "Model/Model.h"
#include "Model/Texture.h"
#include <string>
#include <unordered_map>
#include <d3d11.h>

class GameObjectFactory
{
public:
	static GameObjectFactory& GetInstance();
	bool Init(ID3D11Device* aDevice, ID3D11DeviceContext* aContext);

	GameObject CreateGameObject(const std::string& aModelName);
	Model* GetModel(const std::string& aModelName);

	bool LoadObj(const std::string& aModelName, const std::string& aFilePath);
	bool LoadFbx(const std::string& aModelName, const std::string& aFilePath);

	Texture* GetTexture(const std::string& aFilePath, bool anSRGB);

private:
	GameObjectFactory() = default;

	Model& CreateModel(const std::string& aModelName);
	Model::SubMesh* AddSubMesh(Model& aModel,
	                           const Vertex* aVertices, unsigned int aVertexCount,
	                           const unsigned int* aIndices, unsigned int aIndexCount,
	                           const std::string& aMaterialName = "");
	Texture* FindTexture(const std::string& aFolder, const std::vector<std::string>& someBaseNames, int aSlot);

	ID3D11Device* myDevice = nullptr;
	ID3D11DeviceContext* myContext = nullptr;

	std::unordered_map<std::string, Model> myModels;
	std::unordered_map<std::string, Texture> myTextures;
	Texture myFallbackTextures[TextureSlot::Count];
};
