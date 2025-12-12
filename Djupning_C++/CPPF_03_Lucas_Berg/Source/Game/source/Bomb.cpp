#include "Bomb.h"

#include "CommonUtilities/Random.h"
#include "tge/graphics/GraphicsEngine.h"
#include "tge/texture/TextureManager.h"

Bomb::Bomb()
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();
	myResolution = engine.GetRenderSize();

	mySpriteData.myTexture = engine.GetTextureManager().GetTexture("Sprites/Paratrooper/playerBullet_2.dds");

	mySpriteInstance.myPivot = {0.5f, 1.0f};
	mySpriteInstance.myPosition = {myResolution.x / 2, 1110.0f};
	mySpriteInstance.mySize = mySpriteData.myTexture->CalculateTextureSize();
	mySpriteInstance.mySizeMultiplier = 1;

	myDirection = {0.0f, -1.0f};
	mySpeed = 100.0f;
	myType = EnemyType::Bomb;

	//float spawnChance = globalRNG.RangeFloat(0.0, 100.0f);
}

Bomb::~Bomb()
{
}

void Bomb::Update(float aTimeDelta)
{
	Enemy::Update(aTimeDelta);

	Tga::Vector2f bombVelocity = mySpeed * Tga::Vector2f{0.0f, -1.0f} * aTimeDelta;
	mySpriteInstance.myPosition += bombVelocity;

	if (mySpriteInstance.myPosition.y <= 110)
	{
		myShouldExplode = true;
	}

	if (myOnExplode && myShouldExplode)
	{
		myOnExplode();
	}
}
