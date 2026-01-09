#include "Player.h"

#include "tge/texture/TextureManager.h"
#include "tge/Engine.h"
#include "tge/error/ErrorManager.h"
#include "tge/graphics/GraphicsEngine.h"

Player::Player()
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();
	myResolution = engine.GetRenderSize();

	mySpriteData.myTexture = engine.GetTextureManager().GetTexture("Sprites/Paratrooper/Cannon.png");

	mySpriteInstance.myPivot = {0.5f, 1.0f};
	mySpriteInstance.myPosition = {myResolution.x / 2, 110.0f};
	mySpriteInstance.mySize = mySpriteData.myTexture->CalculateTextureSize();
	mySpriteInstance.mySizeMultiplier = 1;

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

	if (inputLeft && mySpriteInstance.myRotation < 1.2f && !myMachineGunActive)
	{
		mySpriteInstance.myRotation += 0.013f;
	}
	if (inputRight && mySpriteInstance.myRotation > -1.2f && !myMachineGunActive)
	{
		mySpriteInstance.myRotation -= 0.013f;
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
		bullet.Update(aTimeDelta);
	}

	std::erase_if(myBullets, [](const Bullet& bullet)
	{
		return bullet.GetOutOfBounds();
	});


	//UNREFERENCED_PARAMETER(aTimeDelta);
}

void Player::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	aSpriteDrawer.Draw(mySpriteData, mySpriteInstance);
	/*Tga::SpriteBatchScope batch = spriteDrawer.BeginBatch(mySpriteData);
	batch.Draw(mySpriteInstance);*/

	for (auto& bullet : myBullets)
	{
		bullet.Render(aSpriteDrawer);
	}
	//Tga::SpriteBatchScope towerBatch = spriteDrawer.BeginBatch(myTowerData);
	//batch.Draw(myTowerSprite);
}

void Player::Shoot()
{
	auto bullet = Bullet();
	bullet.SetPosition(mySpriteInstance.myPosition);
	bullet.SetDirection({-sinf(mySpriteInstance.myRotation), cosf(mySpriteInstance.myRotation)});

	bullet.SetRotation(mySpriteInstance.myRotation);
	myBullets.push_back(bullet);

	myUIManager->LoseScore();
	myShootTimer = 0.0f;

	myShootSound.Play();
}

void Player::SetSmartBombs(int aSmartBombs)
{
	mySmartBombs = aSmartBombs;
	if (mySmartBombs <= 0) { mySmartBombs = 0; }
}
