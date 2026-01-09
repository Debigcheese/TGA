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
	myEntities.clear();
}

void ParticleSystem::Init(ParticlePreset aPreset)
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();
	myResolution = engine.GetRenderSize();

	myPreset = aPreset;
	ParticleSettings setting{};

	if (aPreset == ParticlePreset::CircleSpread)
	{
		setting.count = 100;
		setting.lifeTime = 3.75f;
		setting.texturePath = "Sprites/Particle.png";
		setting.transform.scale = Tga::Vector2f{1.0f, 1.0f};
	}

	myParticleSetting = setting;
	mySharedData.myTexture = engine.GetTextureManager().GetTexture(myParticleSetting.texturePath.c_str());
}

void ParticleSystem::Update(float aTimeDelta)
{
	myParticleSetting.lifeTime -= aTimeDelta;

	if (myParticleSetting.lifeTime <= 0)
	{
		myIsActive = false;
		if (myOnDeathCallback)
		{
			myOnDeathCallback();
		}
	}

	for (auto& entity : myEntities)
	{
		entity->Update(aTimeDelta);
	}
}

void ParticleSystem::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	Tga::SpriteDrawer& spriteDrawer = aSpriteDrawer;
	Tga::SpriteBatchScope batch = spriteDrawer.BeginBatch(mySharedData);

	for (const auto& entity : myEntities)
	{
		batch.Draw(entity->GetSpriteInstance());
	}
}

void ParticleSystem::Play()
{
	for (int i = 0; i < myParticleSetting.count; ++i)
	{
		auto entity = std::make_unique<Entity>();
		auto moveComp = entity->AddComponent<MovementComponent>();

		entity->SetOnCollided([this](Entity* aEntity)
		{
			if (auto moveComp = aEntity->GetComponent<MovementComponent>())
			{
				moveComp->SetDirection({moveComp->GetMovement().direction.x, moveComp->GetMovement().direction.y * -1});
			}
		});

		if (myPreset == ParticlePreset::CircleSpread)
		{
			MovementData& movementData = myParticleSetting.movementData;

			movementData.speed = globalRNG.RangeFloat(300, 600);
			movementData.direction = {globalRNG.RangeFloat(-0.2f, .2f), globalRNG.RangeFloat(-0.2f, 0.5f)};
			movementData.gravity = 1.0f;

			if (moveComp)
			{
				moveComp->SetMovement(movementData);
			}
			myParticleSetting.transform.scale = 2.0f;
		}

		entity->SetTransform(myParticleSetting.transform);
		entity->SetTexture(myParticleSetting.texturePath);
		myEntities.push_back(std::move(entity));
	}
	myIsActive = true;
}
