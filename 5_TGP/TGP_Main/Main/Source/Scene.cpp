#include "Scene.h"
#include "Engine.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <string>
#include <utility>

#include "AssetPaths.h"
#include "Shader/ShaderFactory.h"

#include "TGAFBXImporter/source/Importer.h"

#include "CommonUtilities/Random.h"
#include "CommonUtilities/math/FMath.h"

bool Scene::Init()
{
	auto& factory = GameObjectFactory::GetInstance();

	myLitShader = ShaderFactory::GetInstance().GetShader("lit");
	myFileTexture = factory.GetTexture("Assets/Textures/texture_2.png", false);

	if (!LoadTerrain())
		return false;

	if (!LoadModels())
		return false;

	CreateObjects();
	CreateLights();

	return true;
}

void Scene::Update(float aTotalTime)
{
	for (auto& point : myPointLights)
	{
		float a = aTotalTime * point.orbitSpeed + point.phase;
		point.position = {
			point.orbitCenter.x + cosf(a) * point.orbitRadius,
			point.orbitCenter.y + sinf(a * 0.5f),
			point.orbitCenter.z + sinf(a) * point.orbitRadius
		};
	}

	for (auto& spot : mySpotLights)
	{
		float a = aTotalTime * spot.orbitSpeed + spot.phase;
		spot.position = {
			spot.orbitCenter.x + cosf(a) * spot.orbitRadius,
			FLOOR_HEIGHT + 12.0f,
			spot.orbitCenter.z + sinf(a) * spot.orbitRadius
		};
		spot.direction = {-spot.position.x * 0.15f, -1.0f, -spot.position.z * 0.15f};
	}
}

bool Scene::LoadTerrain()
{
	auto device = Engine::GetInstance()->GetGraphicsEngine().GetDevice();
	auto& factory = GameObjectFactory::GetInstance();

	std::vector<unsigned int> terrainIndices;
	auto terrainVertices = myTerrain.BuildTerrain(terrainIndices);
	if (!myTerrain.Init(device, terrainVertices, terrainIndices))
		return false;

	const std::pair<std::string, bool> terrainTextures[TERRAIN_TEXTURE_COUNT] = {
		{"Grass_c.png", true},
		{"Rock_c.png", true},
		{"Snow_c.png", true},
		{"Grass_n.png", false},
		{"Rock_n.png", false},
		{"Snow_n.png", false},
		{"Grass_m.png", false},
		{"Rock_m.png", false},
		{"Snow_m.png", false},
	};
	for (int i = 0; i < TERRAIN_TEXTURE_COUNT; ++i)
	{
		myTerrainTextures[i] = factory.GetTexture(terrainTextures[i].first, terrainTextures[i].second);
		if (!myTerrainTextures[i])
		{
			assert(false && "Scene: failed to load terrain texture");
			return false;
		}
	}

	if (!myEnvironmentCubemap.Initialize(
		device, AssetPaths::ResolveWString(L"cube_1024_preblurred_angle3_Skansen3.dds").c_str()))
		return false;

	return true;
}

bool Scene::LoadModels()
{
	auto& factory = GameObjectFactory::GetInstance();

	const std::pair<std::string, std::string> models[] = {
		{"Chest", "Particle_Chest.fbx"},
		{"StoneFloor", "StoneFloor.fbx"},
		{"StoneFloorBlack", "StoneFloor Low.fbx"},
		{"Jeep", "Jeep_done_2.fbx"},
	};
	for (const auto& [name, path] : models)
	{
		if (!factory.LoadFbx(name, path))
		{
			const std::string message = "LoadFbx failed for '" + name + "' (" + path + "): " +
				TGA::FBX::Importer::GetLastError() + "\n";
			OutputDebugStringA(message.c_str());
			assert(false && "Scene: LoadFbx failed, check the path");
			return false;
		}
	}

	return true;
}

void Scene::CreateObjects()
{
	auto& factory = GameObjectFactory::GetInstance();

	constexpr int gridSize = 8;
	constexpr float offset = 3.5f;
	constexpr float offsetMultiplier = 4.f;

	for (int i = 0; i < gridSize; ++i)
	{
		for (int j = 0; j < gridSize; ++j)
		{
			const float posX = ((float)i - offset) * offsetMultiplier;
			const float posZ = ((float)j - offset) * offsetMultiplier;

			GameObject obj;
			switch ((i + j) % 3)
			{
				case 0:
				{
					obj = factory.CreateGameObject("Chest");
					obj.SetScale(0.01f);
					obj.SetPosition({posX, FLOOR_HEIGHT + 0.5f, posZ});
					break;
				}
				case 1:
				{
					obj = factory.CreateGameObject("Cube");
					obj.SetScale(1.5f);
					obj.SetPosition({posX, FLOOR_HEIGHT + 0.75f, posZ});
					break;
				}
				default:
				{
					obj = factory.CreateGameObject("Pyramid");
					obj.SetScale(1.5f);
					obj.SetPosition({posX, FLOOR_HEIGHT, posZ});
					break;
				}
			}
			obj.SetTexture(TextureSlot::Albedo, myFileTexture);
			obj.SetShader(myLitShader);
			myObjects.push_back(obj);
		}
	}

	GameObject stoneFloor = factory.CreateGameObject("StoneFloor");
	stoneFloor.SetShader(myLitShader);
	stoneFloor.SetScale(0.15f);
	stoneFloor.SetPosition({-10.0f, FLOOR_HEIGHT - 1.25f, 5.0f});
	stoneFloor.SetRotation(-90.0f, 0.0f, 0.0f);
	myObjects.push_back(stoneFloor);

	myPointMarker = factory.CreateGameObject("Cube");
	myPointMarker.SetShader(myLitShader);

	mySpotMarker = factory.CreateGameObject("Pyramid");
	mySpotMarker.SetShader(myLitShader);

	myWaterObject = factory.CreateGameObject("Plane");
	myWaterObject.SetShader(ShaderFactory::GetInstance().GetShader("water"));
	myWaterObject.SetScale(100.0f);
	myWaterObject.SetPosition({0.0f, myWaterHeight, 0.0f});
}

void Scene::CreateLights()
{
	const int pointCount = 100;
	const int spotCount = 30;

	for (int i = 0; i < pointCount; ++i)
	{
		PointLight point;
		point.color = {1.0f, globalRNG.RangeFloat(0.35f, 0.85f), 0.15f};
		point.intensity = 5.0f;
		point.range = 8.0f;
		point.orbitCenter = {0.0f, FLOOR_HEIGHT + globalRNG.RangeFloat(2.0f, 5.0f), 0.0f};
		point.orbitRadius = globalRNG.RangeFloat(3.0f, 17.0f);
		point.orbitSpeed = globalRNG.RangeFloat(0.25f, 0.45f);
		point.phase = globalRNG.RangeFloat(0.0f, FMath::Tau);
		myPointLights.push_back(point);
	}

	for (int i = 0; i < spotCount; ++i)
	{
		SpotLight spot;
		spot.color = {0.2f, globalRNG.RangeFloat(0.5f, 0.9f), 1.0f};
		spot.intensity = 100.0f;
		spot.range = 25.0f;
		spot.innerAngle = 0.18f;
		spot.outerAngle = 0.28f;
		spot.orbitRadius = globalRNG.RangeFloat(-5.0f, 17.0f);
		spot.orbitSpeed = -globalRNG.RangeFloat(0.15f, 0.65f);
		spot.phase = globalRNG.RangeFloat(0.0f, FMath::Tau);
		mySpotLights.push_back(spot);
	}
}

std::vector<LightRef> Scene::CollectLightsForObject(const Vector3f& anObjectPosition, float anObjectRadius) const
{
	std::vector<LightRef> result;

	for (int i = 0; i < (int)myPointLights.size(); ++i)
	{
		float dist = (myPointLights[i].position - anObjectPosition).Length();
		if (dist < myPointLights[i].range + anObjectRadius)
			result.push_back({false, i, dist});
	}

	for (int i = 0; i < (int)mySpotLights.size(); ++i)
	{
		float dist = (mySpotLights[i].position - anObjectPosition).Length();
		if (dist < mySpotLights[i].range + anObjectRadius)
			result.push_back({true, i, dist});
	}

	std::sort(result.begin(), result.end(),
	          [](const LightRef& a, const LightRef& b) { return a.distance < b.distance; });

	return result;
}
