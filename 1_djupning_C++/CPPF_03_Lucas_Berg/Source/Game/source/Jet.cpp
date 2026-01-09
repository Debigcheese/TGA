#include "Jet.h"

#include "CommonUtilities/Random.h"
#include "tge/graphics/GraphicsEngine.h"
#include "tge/texture/TextureManager.h"

Jet::Jet()
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();
	myResolution = engine.GetRenderSize();

	mySpriteData.myTexture = engine.GetTextureManager().GetTexture("Sprites/Paratrooper/jet.dds");

	mySpriteInstance.myPivot = {0.5f, 1.0f};
	mySpriteInstance.myPosition = {myResolution.x / 2, 110.0f};
	mySpriteInstance.mySize = mySpriteData.myTexture->CalculateTextureSize();
	mySpriteInstance.mySizeMultiplier = 1;

	myType = EnemyType::Jet;

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

	mySpeed = 200.0f;

	//float spawnChance = globalRNG.RangeFloat(0.0, 100.0f);
}

Jet::~Jet()
{
}

void Jet::Update(float aTimeDelta)
{
	Enemy::Update(aTimeDelta);

	Tga::Vector2f velocity = mySpeed * myDirection * aTimeDelta;
	mySpriteInstance.myPosition += velocity;

	if (myDropBomb && myOnDropBomb)
	{
		myOnDropBomb(mySpriteInstance.myPosition);
		myJetBombDropped = true;
	}

	if (myJetBombDropped)
	{
		myDropBomb = false;
		return;
	}

	if (mySpriteInstance.myPosition.x <= myResolution.x / 2 + 20 && mySpriteInstance.myPosition.x >= myResolution.x / 2
		- 20)
	{
		myDropBomb = true;
	}
}


// 15
