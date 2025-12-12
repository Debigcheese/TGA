#include "Enemy.h"

#include "tge/texture/TextureManager.h"
#include "CommonUtilities/Random.h"
#include "tge/graphics/GraphicsEngine.h"

Enemy::Enemy()
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();
	myResolution = engine.GetRenderSize();

	for (int i = 0; i < TEXTURE_SIZE; ++i)
	{
		std::string texturePath = "Sprites/Paratrooper/explosion_" + std::to_string(i + 1) + ".dds";
		myTextures[i] = engine.GetTextureManager().GetTexture(texturePath.c_str());
	}
}

Enemy::~Enemy()
{
}

void Enemy::Update(float aTimeDelta)
{
	if (CheckOutOfBounds())
	{
		myLifeState = LifeState::Dead;
	}
	if (myLifeState == LifeState::Dead)
	{
		mySpeed = 0.0f;
		UpdateDeathAnimation(aTimeDelta);

		if (myAnimTimer >= 1)
		{
			myLifeState = LifeState::Destroy;
		}
	}

	UNREFERENCED_PARAMETER(aTimeDelta);
}

void Enemy::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	if (myLifeState == LifeState::Destroy)
	{
		return;
	}

	auto& spriteDrawer = aSpriteDrawer;
	spriteDrawer.Draw(mySpriteData, mySpriteInstance);
}

void Enemy::UpdateDeathAnimation(float aTimeDelta)
{
	myAnimTimer += aTimeDelta;
	mySpriteData.myTexture = myTextures[static_cast<int>(myAnimTimer * 4) % TEXTURE_SIZE];
}

bool Enemy::CheckOutOfBounds()
{
	const auto& position = mySpriteInstance.myPosition;

	if (position.x < -50 || position.x > myResolution.x + 50)
	{
		return true;
	}
	if (position.y < -50 || position.y > myResolution.y + 50)
	{
		return true;
	}
	return false;
}

void Enemy::OnDeath()
{
	myLifeState = LifeState::Dead;
	mySpriteData.myTexture = myTextures[0];
	mySpriteInstance.mySize = mySpriteData.myTexture->CalculateTextureSize();
	mySpeed = 0;

	if (myOnDeath)
	{
		myOnDeath(this);
	}

	//myParticleSystem.Play();
}
