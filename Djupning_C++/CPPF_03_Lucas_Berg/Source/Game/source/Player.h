#pragma once
#include "Bullet.h"
#include "UIManager.h"
#include "tge/math/Vector2.h"
#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
#include "tge/sprite/sprite.h"
#include "CommonUtilities/InputHandler.h"
#include "tge/audio/audio.h"

using Input = CommonUtilities::InputHandler;

class Player
{
public:
	Player();
	~Player();
	void Init(Input* aInput, UIManager& UIManager);

	void Update(float aTimeDelta);
	void Render(Tga::SpriteDrawer& aSpriteDrawer);
	void Shoot();

	void PossessPlayer(Input* aInput) { myInput = aInput; }
	std::vector<Bullet> GetBullets() const { return myBullets; }

	void SetOnInputPressCallback(const std::function<void(char)> aCallback) { myOnInputPress = aCallback; }
	std::function<void(GameState)> myOnGameStateCallback;

	int GetSmartBombs() const { return mySmartBombs; }
	void SetSmartBombs(int aSmartBombs);

private:
	Input* myInput;
	UIManager* myUIManager;

	std::function<void(char)> myOnInputPress;

	Tga::Sprite2DInstanceData mySpriteInstance;
	Tga::SpriteSharedData mySpriteData;

	Tga::Sprite2DInstanceData myTowerSprite;
	Tga::SpriteSharedData myTowerData;

	Tga::Vector2f myResolution;
	Tga::Vector2f myRotation;

	int mySmartBombs = 3;
	float myShootCooldown = 0.55f;
	float myShootTimer = 0.0f;

	float myMachineGunCD = 0.1f;
	float myMachineGunActivateTimer = 1.0f;
	bool myMachineGunActive = false;

	std::vector<Bullet> myBullets;

	Tga::Audio myShootSound;
};
