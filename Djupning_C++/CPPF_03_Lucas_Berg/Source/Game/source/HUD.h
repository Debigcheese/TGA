#pragma once
#include "SharedTypes.h"
#include "GameState.h"
#include "tge/Engine.h"
#include "tge/text/text.h"
#include "CommonUtilities/UtilityFunctions.h"
#include "tge/shaders/SpriteShader.h"

enum class TextType
{
	Score,
	GameOver,
	Intro,
	PressStart,
	Restart
};

class HUD
{
public:
	HUD();
	~HUD();

	void Init(Tga::Engine& aEngine);
	void InitSpriteData(Tga::Engine& aEngine);
	void InitTextData();

	void Render(Tga::SpriteDrawer& aSpriteDrawer);
	void Update(const GameState& aGameState);

	Tga::Text GetText();

	void ShowIntro(bool aShowIntro) { myShowIntro = aShowIntro; }
	void ShowRestart(bool aShowRestart) { myShowRestart = aShowRestart; }
	void ShowFinish(bool aShowFinish) { myShowFinish = aShowFinish; }

private:
	Tga::Vector2f myScreenResolution;

	std::vector<SpriteData> mySprite;
	std::vector<Tga::Text> myTexts;
	std::vector<Tga::Text> myTextsToRender;

	Tga::SpriteShader myShader;

	bool myShowIntro = true;
	bool myShowRestart = false;
	bool myShowFinish = false;
};
