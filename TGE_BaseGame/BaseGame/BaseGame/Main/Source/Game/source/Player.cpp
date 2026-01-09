#include "Player.h"

#include "MovementComponent.h"
#include "tge/texture/TextureManager.h"
#include "tge/Engine.h"
#include "tge/error/ErrorManager.h"
#include "tge/graphics/GraphicsEngine.h"

Player::Player()
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();
	myResolution = engine.GetRenderSize();

	myEntity.SetTexture(engine.GetTextureManager().GetTexture("Sprites/Cannon.png"));

	myBulletTexture = engine.GetTextureManager().GetTexture("Sprites/playerBullet.png");

	myEntity.SetPivot({0.5f, 1.0f});
	myEntity.SetPosition({myResolution.x / 2, 110.0f});
	myEntity.SetScale({1.0f, 1.0f});

	myShootSound.Init("Audio/projectile_arcade.wav", false);
}

Player::~Player()
{
}

void Player::Init(Input* aInput, UIManager& UIManager)
{
	myInput = aInput;
	myUIManager = &UIManager;
}

void Player::Update(float aTimeDelta)
{
	if (!myInput)
	{
		return;
	}

	bool mouseClicked = myInput->IsKeyDown(KEY_LMB);
	bool spacePressed = myInput->IsKeyPressed(KEY_SPACE);
	bool pausePressed = myInput->IsKeyPressed('P');
	bool IPressed = myInput->IsKeyPressed('I');

	if (mouseClicked && myOnInputPress) { myOnInputPress(KEY_LMB); }
	if (spacePressed && myOnInputPress) { myOnInputPress(KEY_SPACE); }
	if (pausePressed && myOnInputPress) { myOnInputPress('P'); }
	if (IPressed && myOnInputPress) { myOnInputPress('I'); }

	if (myUIManager->GetGameState() != GameState::InGame) { return; }

	bool inputLeft = (myInput->IsKeyDown('A') || myInput->IsKeyDown(KEY_ARROW_L));
	bool inputRight = (myInput->IsKeyDown('D') || myInput->IsKeyDown(KEY_ARROW_R));
	bool inputUp = (myInput->IsKeyPressed('W') ||
		myInput->IsKeyPressed(KEY_ARROW_UP) ||
		myInput->IsKeyPressed(KEY_SPACE));

	bool inputUpHeld = myInput->IsKeyDown(KEY_ARROW_UP) || myInput->IsKeyDown(KEY_SPACE);

	bool useSmartBomb = myInput->IsKeyPressed('S');

	if (inputLeft && myEntity.GetSpriteInstance().myRotation < 1.2f && !myMachineGunActive)
	{
		myEntity.SetRotation(myEntity.GetRotation() + 0.013f);
	}
	if (inputRight && myEntity.GetSpriteInstance().myRotation > -1.2f && !myMachineGunActive)
	{
		myEntity.SetRotation(myEntity.GetRotation() - 0.013f);
	}

	myShootTimer += aTimeDelta;

	if (inputUpHeld)
	{
		myMachineGunActivateTimer -= aTimeDelta;

		if (myMachineGunActivateTimer <= 0 && myMachineGunCD <= myShootTimer)
		{
			myMachineGunActive = true;
			Shoot();
		}
	}
	else
	{
		myMachineGunActivateTimer = 1.0f;
		myMachineGunActive = false;
	}

	if (inputUp && myShootCooldown < myShootTimer)
	{
		Shoot();
	}

	if (useSmartBomb && myOnInputPress)
	{
		myOnInputPress('S');
	}

	for (auto& bullet : myBullets)
	{
		bullet->Update(aTimeDelta);
	}

	//std::erase_if(myBullets, [](const Bullet& bullet)
	//{
	//	return bullet.GetOutOfBounds();
	//});

	for (auto& pendingParticleSystem : myPendingParticleSystems)
	{
		myParticleSystems.push_back(std::move(pendingParticleSystem));
	}

	myPendingParticleSystems.clear();

	for (auto& particleSystem : myParticleSystems)
	{
		particleSystem->Update(aTimeDelta);
	}

	std::erase_if(myParticleSystems, [](const std::unique_ptr<ParticleSystem>& aParticleSystem)
	{
		return !aParticleSystem->GetIsActive();
	});

	//UNREFERENCED_PARAMETER(aTimeDelta);
}

void Player::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	aSpriteDrawer.Draw(myEntity.GetSpriteData(), myEntity.GetSpriteInstance());

	Tga::SpriteSharedData spriteSharedData;
	spriteSharedData.myTexture = myBulletTexture;
	Tga::SpriteBatchScope batch = aSpriteDrawer.BeginBatch(spriteSharedData);

	for (auto& bullet : myBullets)
	{
		batch.Draw(bullet->GetSpriteInstance());
	}

	for (auto& particleSystem : myParticleSystems)
	{
		particleSystem->Render(aSpriteDrawer);
	}
	//Tga::SpriteBatchScope towerBatch = spriteDrawer.BeginBatch(myTowerData);
	//batch.Draw(myTowerSprite);
}

void Player::Shoot()
{
	auto bulletEntity = std::make_unique<Entity>();
	bulletEntity->SetTexture(myBulletTexture);
	bulletEntity->SetScale(2.0f);

	if (auto bulletMovement = bulletEntity->AddComponent<MovementComponent>())
	{
		bulletMovement->SetDirection({-sinf(myEntity.GetRotation()), cosf(myEntity.GetRotation())});
		bulletMovement->SetSpeed(600.0f);
		bulletMovement->SetGravity(0.0f);
	}

	myBullets.push_back(std::move(bulletEntity));

	myUIManager->LoseScore();
	myShootTimer = 0.0f;
	myShootSound.Play();
}

void Player::SetSmartBombs(int aSmartBombs)
{
	mySmartBombs = aSmartBombs;
	if (mySmartBombs <= 0)
	{
		mySmartBombs = 0;
	}
}
