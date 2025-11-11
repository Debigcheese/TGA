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
	void InitTextData();

	void Render(Tga::SpriteDrawer& aSpriteDrawer);
	void Update(float aTimeDelta, const GameState& aGameState);

	Tga::Text GetText();
	void LerpTextSize(float aSize, float aDuration);

	void SetGameOverStr(const std::string& aString);
	void ShowIntro(bool aShowIntro) { myShowIntro = aShowIntro; }
	void ShowRestart(bool aShowRestart) { myShowRestart = aShowRestart; }
	void ShowFinish(bool aShowFinish) { myShowFinish = aShowFinish; }

private:
	SpriteData mySprite = {{}, {}};
	Tga::TextureResource* myTitleBorderTexture;
	Tga::Vector2f myTitleBorderPos;

	Tga::SpriteShader myShader;

	Tga::Vector2f myScreenResolution;

	Tga::Text myScoreTx;
	std::string myScoreStr;
	std::string myEnemyScoreStr;

	LerpData myScoreLerpData = {1, 1, 1.2f, 0.0f, 0.2f, 0.0f, false};

	struct GameOverData
	{
		Tga::Text myGameOverText;
		std::string myGameOverStr;
	};

	GameOverData myGameOverData;

	Tga::Text myIntroText;
	Tga::Vector2f myIntroTextPos;
	Tga::Text myPressStartText;
	Tga::Text myRestartText;

	bool myShowIntro = true;
	bool myShowRestart = false;
	bool myShowFinish = false;
};
