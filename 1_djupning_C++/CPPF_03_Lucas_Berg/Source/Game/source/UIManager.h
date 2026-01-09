#pragma once
#include <vector>
#include <memory>
#include "Button.h"
#include "RenderCommand.h"
#include "CommonUtilities/InputHandler.h"
#include "tge/text/text.h"

using Input = CommonUtilities::InputHandler;

enum GameState
{
	Intro = 0,
	InGame = 2,
	Death = 3,
	Restart = 4,
};

enum class TextId
{
	Start,
	Instructions,
	Score,
	GameOver,
	PlayAgain,
	Title,
	highScore_1,
	highScore_2,
	highScore_3,
	Paused,
	BombCount
};

namespace Tga
{
	class SpriteBatchScope;
}

class UIManager
{
public:
	UIManager();
	~UIManager();

	void Init();
	void Update(float aDeltaTime, const Input* aInput);
	void Render(Tga::SpriteDrawer& aSpriteDrawer);

	void GainScore(int aScore) { myBulletScore += aScore; }
	void LoseScore();

	void SetSmartBombText(int aAmount) { mySmartBombs = aAmount; }

	void StartGame();
	void GameOver();
	void RestartGame();
	void PauseGame();
	void ShowInstructions();

	void CalculateHighScore();

	void SetOnStartGameCallback(std::function<void()> aCallback);
	void OnStartButtonClicked();

	GameState GetGameState() const { return myGameState; }
	bool GetIsPaused() const { return myIsPaused; }

private:
	Tga::Vector2ui myResolution;

	RenderCommand myRenderCommand;

	std::vector<std::unique_ptr<Button>> myButtons;
	std::unordered_map<TextId, Tga::Text> myTexts;

	std::function<void()> myOnStartGameCallback;

	GameState myGameState = GameState::Intro;
	bool myIsPaused = false;
	bool myShowInstructions = false;
	float myDeathScreenDuration = 2.0f;

	int myBulletScore = 30;
	int mySmartBombs = 3;

	int myHighScores[3] = {-1, -1, -1};
};
