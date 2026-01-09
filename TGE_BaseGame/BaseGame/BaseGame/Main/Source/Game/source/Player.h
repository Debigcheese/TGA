#pragma once
#include "ParticleSystem.h"
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
	std::vector<std::unique_ptr<Entity>>& GetBullets() { return myBullets; }

	void SetOnInputPressCallback(const std::function<void(char)> aCallback) { myOnInputPress = aCallback; }
	std::function<void(GameState)> myOnGameStateCallback;

	int GetSmartBombs() const { return mySmartBombs; }
	void SetSmartBombs(int aSmartBombs);

private:
	Input* myInput;
	UIManager* myUIManager;

	std::function<void(char)> myOnInputPress;

	Tga::Vector2f myResolution;
	Tga::Vector2f myRotation;

	int mySmartBombs = 3;
	float myShootCooldown = 0.55f;
	float myShootTimer = 0.0f;

	float myMachineGunCD = 0.1f;
	float myMachineGunActivateTimer = 1.0f;
	bool myMachineGunActive = false;

	Entity myEntity;

	Tga::TextureResource* myBulletTexture;
	std::vector<std::unique_ptr<Entity>> myBullets;

	Tga::Audio myShootSound;

	std::vector<std::unique_ptr<ParticleSystem>> myParticleSystems;
	std::vector<std::unique_ptr<ParticleSystem>> myPendingParticleSystems;
};
