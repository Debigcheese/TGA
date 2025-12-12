#include "ParticleSystem.h"

#include "CommonUtilities/Random.h"
#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
#include "tge/graphics/GraphicsEngine.h"
#include "tge/texture/TextureManager.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
	myGameObjects.clear();
}

void ParticleSystem::Init(const EmitterSetting& aSetting)
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();
	myResolution = engine.GetRenderSize();

	myEmitterSetting = aSetting;
	mySharedData.myTexture = engine.GetTextureManager().GetTexture("Sprites/Paratrooper/Particle.png");
}

void ParticleSystem::Update(float aTimeDelta)
{
	myEmitterSetting.lifeTime -= aTimeDelta;

	if (myEmitterSetting.lifeTime <= 0)
	{
		myIsActive = false;
		if (myOnDeathCallback)
		{
			myOnDeathCallback();
		}
	}
	for (auto& gameObject : myGameObjects)
	{
		gameObject.Update(aTimeDelta);
	}
}

void ParticleSystem::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	Tga::SpriteDrawer& spriteDrawer = aSpriteDrawer;
	Tga::SpriteBatchScope batch = spriteDrawer.BeginBatch(mySharedData);

	for (const auto& gameObject : myGameObjects)
	{
		batch.Draw(gameObject.GetSpriteInstance());
	}
}

void ParticleSystem::Play()
{
	for (int i = 0; i < myEmitterSetting.count; ++i)
	{
		auto gameObject = GameObject();

		MovementData movementData;
		movementData.speed = globalRNG.RangeFloat(100, 300);
		movementData.direction = globalRNG.RangeFloat(-1, 1);
		gameObject.SetMovement(movementData);

		Tga::Sprite2DInstanceData spriteInstance;
		spriteInstance.myPosition = mySpriteInstance.myPosition;
		gameObject.SetSpriteInstance(spriteInstance);

		Tga::SpriteSharedData sharedData;
		sharedData.myTexture = mySharedData.myTexture;
		gameObject.SetSpriteSharedData(sharedData);

		myGameObjects.push_back(gameObject);
	}
	myIsActive = true;
}
