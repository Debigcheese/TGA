#include "GameObject.h"

#include "tge/Engine.h"
#include "tge/texture/TextureManager.h"

GameObject::GameObject()
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();
	myResolution = engine.GetRenderSize();

	mySpriteData.myTexture = engine.GetTextureManager().GetTexture("Sprites/Paratrooper/Particle.png");

	mySpriteInstance.myPivot = {0.5f, 1.0f};
	mySpriteInstance.myPosition = {myResolution.x / 2, 110.0f};
	mySpriteInstance.mySize = mySpriteData.myTexture->CalculateTextureSize();
	mySpriteInstance.mySizeMultiplier = 1;
}

GameObject::~GameObject()
{
}

void GameObject::Update(float aTimeDelta)
{
	const Tga::Vector2f speed = myMovement.speed;

	myMovement.direction.y -= myMovement.gravity * 0.001f * aTimeDelta;
	myMovement.velocity = myMovement.direction * speed * aTimeDelta;
	mySpriteInstance.myPosition += myMovement.velocity;
}
