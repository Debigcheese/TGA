#include "Entity.h"

#include "tge/Engine.h"
#include "tge/texture/TextureManager.h"
#include <algorithm>

#include "tge/math/CommonMath.h"

Entity::Entity()
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();
	myResolution = engine.GetRenderSize();

	mySpriteData.myTexture = engine.GetTextureManager().GetTexture("Sprites/Particle.png");

	mySpriteInstance.myPivot = {0.5f, 1.0f};
	mySpriteInstance.myPosition = {myResolution.x / 2, 110.0f};
	mySpriteInstance.mySizeMultiplier = {1.0f, 1.0f};
	mySpriteInstance.mySize = Tga::Vector2f{
		mySpriteData.myTexture->CalculateTextureSize()
	} * mySpriteInstance.mySizeMultiplier;
}

Entity::~Entity() = default;

void Entity::Update(float aTimeDelta)
{
	for (auto& component : myComponents)
	{
		component->Update(aTimeDelta);
	}
}

void Entity::SetTransform(const Transform& aTransform)
{
	mySpriteInstance.myPosition = aTransform.position;
	SetScale(aTransform.scale);
	mySpriteInstance.myRotation = aTransform.rotation;
}

Transform Entity::GetTransform()
{
	return {
		Transform{
			mySpriteInstance.myPosition,
			mySpriteInstance.myRotation,
			mySpriteInstance.mySize,
			mySpriteInstance.myPivot
		}
	};
}

void Entity::SetTexture(const std::string& aTexturePath)
{
	mySpriteData.myTexture = Tga::Engine::GetInstance()->GetTextureManager().GetTexture(aTexturePath.c_str());
}

void Entity::OnCollided()
{
	if (myOnCollidedCallback)
	{
		myOnCollidedCallback(this);
	}
}

void Entity::SetRotation(float aRotation)
{
	mySpriteInstance.myRotation = aRotation;
}

void Entity::SetScale(Tga::Vector2f aScale)
{
	mySpriteInstance.mySizeMultiplier = {std::abs(aScale.x), std::abs(aScale.y)};
	if (mySpriteData.myTexture)
	{
		mySpriteInstance.mySize = static_cast<Tga::Vector2f>(mySpriteData.myTexture->CalculateTextureSize()) *
			mySpriteInstance.mySizeMultiplier;
	}

	if (aScale.x < 0)
	{
		mySpriteInstance.mySize.x = -mySpriteInstance.mySize.x;
	}
}

void Entity::SetPivot(Tga::Vector2f aPivot)
{
	mySpriteInstance.myPivot = aPivot;
}
