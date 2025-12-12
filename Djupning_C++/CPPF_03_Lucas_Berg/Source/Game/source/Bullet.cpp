#include "Bullet.h"
#include "tge/Engine.h"
#include "tge/error/ErrorManager.h"
#include "tge/graphics/GraphicsEngine.h"
#include "tge/texture/TextureManager.h"

Bullet::Bullet()
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();
	myResolution = engine.GetRenderSize();

	mySpriteData.myTexture = engine.GetTextureManager().GetTexture("Sprites/Paratrooper/playerBullet_2.dds");
	//mySpriteData.myTexture = engine.GetTextureManager().GetTexture("Sprites/Paratrooper/bomb.png");

	mySpriteInstance.myPivot = {0.5f, 0.5f};
	mySpriteInstance.myPosition = {myResolution.x / 2, myResolution.y / 2};
	mySpriteInstance.mySize = mySpriteData.myTexture->CalculateTextureSize();
	myDirection = Tga::Vector2f(0.0f, 1.0f);
	mySpriteInstance.mySizeMultiplier = .5f;
}

Bullet::~Bullet()
{
}

void Bullet::Update(float aTimeDelta)
{
	Tga::Vector2f velocity = mySpeed * myDirection * aTimeDelta;
	mySpriteInstance.myPosition += velocity;

	CheckOutOfBounds();
}

void Bullet::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	auto& spriteDrawer = aSpriteDrawer;
	spriteDrawer.Draw(mySpriteData, mySpriteInstance);
}

void Bullet::CheckOutOfBounds()
{
	const auto& position = mySpriteInstance.myPosition;

	if (position.x < 0 || position.x > myResolution.x)
	{
		myOutOfBounds = true;
	}
	if (position.y < 0 || position.y > myResolution.y)
	{
		myOutOfBounds = true;
	}
}
