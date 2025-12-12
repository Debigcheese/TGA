#include "Helicopter.h"
#include "CommonUtilities/Random.h"
#include "tge/texture/TextureManager.h"

Helicopter::Helicopter()
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();
	myResolution = engine.GetRenderSize();

	for (int i = 0; i < TEXTURE_SIZE; ++i)
	{
		std::string texturePath = "Sprites/Paratrooper/chopper_" + std::to_string(i + 1) + ".dds";
		myTextures[i] = engine.GetTextureManager().GetTexture(texturePath.c_str());
	}

	mySpriteData.myTexture = myTextures[0];

	mySpriteInstance.myPivot = {0.5f, 1.0f};
	mySpriteInstance.myPosition = {myResolution.x / 2, 110.0f};
	mySpriteInstance.mySize = mySpriteData.myTexture->CalculateTextureSize();
	mySpriteInstance.mySizeMultiplier = 1;

	myType = EnemyType::Helicopter;

	mySide = static_cast<Side>(globalRNG.RangeInt(0, 1));
	myDirection.y = 0.0f;

	if (mySide == Side::Left)
	{
		mySpriteInstance.myPosition = {0.0f, myResolution.y - 110.0f};
		myDirection.x = 1.0f;
	}
	else
	{
		mySpriteInstance.myPosition = {myResolution.x, myResolution.y - 80.0f};
		myDirection.x = -1.0f;
		mySpriteInstance.mySize.x = -mySpriteInstance.mySize.x;
	}

	float spawnChance = globalRNG.RangeFloat(0.0, 100.0f);

	if (spawnChance <= 40)
	{
		mySpawnTrooper = SpawnTrooper::NeverSpawn;
		return;
	}
	myTimeBeforeParatrooper = globalRNG.RangeFloat(2.0, 4.0f);
}

Helicopter::~Helicopter()
{
}

void Helicopter::Update(float aTimeDelta)
{
	Enemy::Update(aTimeDelta);

	UpdateAnimation(aTimeDelta);

	Tga::Vector2f velocity = mySpeed * myDirection * aTimeDelta;
	mySpriteInstance.myPosition += velocity;

	myTimeBeforeParatrooper -= aTimeDelta;

	if (myTimeBeforeParatrooper <= 0 && mySpawnTrooper != SpawnTrooper::NeverSpawn)
	{
		mySpawnTrooper = SpawnTrooper::ShouldSpawn;
		myTimeBeforeParatrooper = 100.0f;
	}

	if (mySpawnTrooper == ShouldSpawn && myOnSpawnTrooper)
	{
		myOnSpawnTrooper(GetPosition());
		mySpawnTrooper = HasSpawned;
	}
}

void Helicopter::UpdateAnimation(float aTimeDelta)
{
	if (myLifeState == LifeState::Dead)
	{
		return;
	}
	myAnimTimer += aTimeDelta;
	mySpriteData.myTexture = myTextures[static_cast<int>(myAnimTimer * 10) % TEXTURE_SIZE];
}
