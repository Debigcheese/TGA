#pragma once
#include <vector>
#include <memory>
#include "Button.h"
#include "RenderCommand.h"
#include "CommonUtilities/InputHandler.h"
#include "tge/text/text.h"

using Input = CommonUtilities::InputHandler;

enum class GameState
{
	Intro = 0,
	InGame = 2,
	Death = 3,
	Restart = 4,
};

enum class TextVisibility
{
	Intro,
	InGame,
	GameOver,
	Restart,
	Instructions,
	Paused,
	Always
};

struct UIText
{
	Tga::Text text;
	std::string uniqueId;
	TextVisibility textVisibility;
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
	void InitTextData();

	void Update(float aDeltaTime, const Input* aInput);
	void UpdateUsernameInput(const Input* aInput);
	void Render(Tga::SpriteDrawer& aSpriteDrawer);

	Tga::Text& GetText(const std::string& aUniqueId);
	void SetTextVisibility(UIText& aText, const std::string& aVisibility);
	bool ShouldRender(TextVisibility aTextVisibility) const;

	void SetSmartBombText(int aAmount) { mySmartBombs = aAmount; }

	//GAMESTATE
	void StartGame();
	void GameOver();
	void RestartGame();
	void PauseGame();
	void ShowInstructions();
	void SubmitName();

	void GainScore(int aScore) { myBulletScore += aScore; }
	void LoseScore();
	void CalculateHighScore();

	void SetOnStartGameCallback(std::function<void()> aCallback);
	void OnStartButtonClicked();

	GameState GetGameState() const { return myGameState; }
	bool GetIsPaused() const { return myIsPaused; }

private:
	Tga::Vector2ui myResolution;

	std::vector<std::unique_ptr<Button>> myButtons;
	std::vector<UIText> myTexts;

	std::function<void()> myOnStartGameCallback;

	GameState myGameState = GameState::Intro;
	bool myIsPaused = false;
	bool myShowInstructions = false;
	bool myIsEnteringUsername = true;
	std::string myUserName;

	float myDeathScreenDuration = 2.0f;
	int myBulletScore = 30;
	int mySmartBombs = 3;
	std::array<int, 3> myHighScores = {-1, -1, -1};
};
