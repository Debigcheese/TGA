//#include "Enemy.h"
//
//#include "tge/texture/TextureManager.h"
//#include "CommonUtilities/Random.h"
//#include "tge/graphics/GraphicsEngine.h"
//
//Enemy::Enemy()
//{
//	Tga::Engine& engine = *Tga::Engine::GetInstance();
//
//	for (int i = 0; i < DEATH_TEXTURE_SIZE; ++i)
//	{
//		std::string texturePath = "Sprites/explosion_" + std::to_string(i + 1) + ".png";
//		myDeathTextures[i] = engine.GetTextureManager().GetTexture(texturePath.c_str());
//	}
//}
//
//Enemy::~Enemy()
//{
//}
//
//void Enemy::Update(float aTimeDelta)
//{
//	myEntity.Update(aTimeDelta);
//
//	if (CheckOutOfBounds())
//	{
//		myLifeState = LifeState::Dead;
//	}
//	if (myLifeState == LifeState::Dead)
//	{
//		myEntity.SetSpeed(0.0);
//
//		UpdateDeathAnimation(aTimeDelta);
//
//		if (myDeathAnimTimer >= 1)
//		{
//			myLifeState = LifeState::Destroy;
//		}
//	}
//
//	UNREFERENCED_PARAMETER(aTimeDelta);
//}
//
//void Enemy::Render(Tga::SpriteDrawer& aSpriteDrawer)
//{
//	if (myLifeState == LifeState::Destroy)
//	{
//		return;
//	}
//
//	auto& spriteDrawer = aSpriteDrawer;
//	spriteDrawer.Draw(myEntity.GetSpriteData(), myEntity.GetSpriteInstance());
//}
//
//void Enemy::UpdateDeathAnimation(float aTimeDelta)
//{
//	myDeathAnimTimer += aTimeDelta;
//	myEntity.SetTexture(myDeathTextures[static_cast<int>(myDeathAnimTimer * 4) % DEATH_TEXTURE_SIZE]);
//}
//
//bool Enemy::CheckOutOfBounds()
//{
//	const auto& position = myEntity.GetPosition();
//	const auto& resolution = myEntity.GetResolution();
//
//	if (position.x < -50 || position.x > resolution.x + 50)
//	{
//		return true;
//	}
//	if (position.y < -50 || position.y > resolution.y + 50)
//	{
//		return true;
//	}
//	return false;
//}
//
//void Enemy::OnDeath()
//{
//	myLifeState = LifeState::Dead;
//	myEntity.SetTexture(myDeathTextures[0]);
//	myEntity.SetScale(1.0f);
//	myEntity.SetSpeed(0.0f);
//
//	if (myOnDeath)
//	{
//		myOnDeath(this);
//	}
//}
