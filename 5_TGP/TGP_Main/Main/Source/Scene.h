#pragma once
#include <vector>
#include "GameObject/GameObjectFactory.h"
#include "Graphics/Lights.h"
#include "Model/TerrainMesh.h"
#include "Model/Texture.h"
#include "Shader/Shader.h"
#include "Cubemap.h"

#include "CommonUtilities/math/vector3.h"

struct DirectionalLightConfig
{
	Vector3f direction = {-0.4f, -1.0f, 0.3f};
	Vector3f color = {1.0f, 0.95f, 0.85f};
	float intensity = 0.18f;
	Vector3f ambientSky = {0.03f, 0.04f, 0.05f};
	Vector3f ambientGround = {0.03f, 0.03f, 0.04f};
	float ambientIntensity = 0.4f;
};

static constexpr float FLOOR_HEIGHT = 30.0f;
static constexpr int TERRAIN_TEXTURE_COUNT = 9;

class Scene
{
public:
	bool Init();
	void Update(float aTotalTime);

	std::vector<LightRef> CollectLightsForObject(const Vector3f& anObjectPosition, float anObjectRadius) const;

	const std::vector<GameObject>& GetObjects() const { return myObjects; }
	const std::vector<PointLight>& GetPointLights() const { return myPointLights; }
	const std::vector<SpotLight>& GetSpotLights() const { return mySpotLights; }
	const DirectionalLightConfig& GetDirectionalLight() const { return myDirectionalLight; }
	const GameObject& GetPointMarker() const { return myPointMarker; }
	const GameObject& GetSpotMarker() const { return mySpotMarker; }
	const TerrainMesh& GetTerrain() const { return myTerrain; }
	const Texture* GetTerrainTexture(int anIndex) const { return myTerrainTextures[anIndex]; }
	const Cubemap& GetEnvironmentCubemap() const { return myEnvironmentCubemap; }
	const GameObject& GetWaterObject() const { return myWaterObject; }
	float GetWaterHeight() const { return myWaterHeight; }

private:
	bool LoadTerrain();
	bool LoadModels();
	void CreateObjects();
	void CreateLights();

	Shader* myLitShader = nullptr;
	Texture* myFileTexture = nullptr;

	DirectionalLightConfig myDirectionalLight;
	std::vector<PointLight> myPointLights;
	std::vector<SpotLight> mySpotLights;
	GameObject myPointMarker;
	GameObject mySpotMarker;

	std::vector<GameObject> myObjects;

	TerrainMesh myTerrain;
	Texture* myTerrainTextures[TERRAIN_TEXTURE_COUNT] = {};
	Cubemap myEnvironmentCubemap;

	GameObject myWaterObject;
	float myWaterHeight = -5.0f;
};
