#include "UIManager.h"
#include <tge/engine.h>

#include "Paratrooper.h"
#include "tge/error/ErrorManager.h"
#include "tge/graphics/GraphicsEngine.h"
#include "tge/text/TextService.h"
#include "tge/texture/TextureManager.h"


UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::Init()
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();
	myResolution = engine.GetRenderSize();

	Tga::Vector2f screenCenter = {
		static_cast<float>(myResolution.x) * 0.5f,
		static_cast<float>(myResolution.y) * 0.5f
	};

	auto startButton = std::make_unique<Button>();
	startButton->SetPosition(screenCenter + Tga::Vector2f{30.0f, -90.0f});
	startButton->SetSize({150.0f, 45.0f});
	startButton->SetTexture("Sprites/UI/Button.png");

	auto startText = Tga::Text("Text/Ac437_IBM_CGA.ttf", Tga::FontSize_12);
	startText.SetPosition(screenCenter + Tga::Vector2f{-150.0f, -100.0f});
	startText.SetText("         Play\n\n"
		"Press 'Space' to play\n"
		"Hold 'I' for instructions\n"
		"Press 'ESC' to quit\n\n"
		"Game made by Lucas Berg");

	auto titleText = Tga::Text("Text/Ac437_IBM_CGA.ttf", Tga::FontSize_48);
	titleText.SetPosition(screenCenter + Tga::Vector2f{-275.0f, +200.0f});
	titleText.SetText("PARATROOPERS");

	auto instructionsText = Tga::Text("Text/Ac437_IBM_CGA.ttf", Tga::FontSize_10);
	instructionsText.SetPosition(screenCenter + Tga::Vector2f{400.0f, -90.0f});
	instructionsText.SetText(
		"*Your Mission* \n"
		"Dont let 4 paratroopers land\n"
		"on one side of your gun base\n"
		"or they'll blow it up.\n"
		"After helicopters, watch for\n"
		"jet bombers with deadly aim! \n\n"
		"Controls: \n"
		"'<-' or 'A' - counterclockwise \n"
		"'->' or 'D' - clockwise\n"
		"'^' or 'W' - stop and fire\n"
		"Scoring:\n "
		"HELICOPTER/JET - 10 points\n"
		"PARATROOPER - 5 points\n"
		"BOMB - 30 points\n"
		"Each bullet - -1 point\n");

	auto scoreText = Tga::Text("Text/Ac437_IBM_CGA.ttf", Tga::FontSize_12);
	scoreText.SetPosition(screenCenter + Tga::Vector2f{-60.0f, +150.0f});
	scoreText.SetText("Points: ");

	auto gameOverText = Tga::Text("Text/Ac437_IBM_CGA.ttf", Tga::FontSize_36);
	gameOverText.SetPosition(screenCenter + Tga::Vector2f{-100.0f, -90.0f});
	gameOverText.SetText("Game Over!");

	auto playAgain = Tga::Text("Text/Ac437_IBM_CGA.ttf", Tga::FontSize_12);
	playAgain.SetPosition(screenCenter + Tga::Vector2f{-100.0f, -10.0f});
	playAgain.SetText("Press 'Space' to play again");

	auto highScoreText_1 = Tga::Text("Text/Ac437_IBM_CGA.ttf", Tga::FontSize_12);
	highScoreText_1.SetPosition(screenCenter + Tga::Vector2f{-400.0f, +150.0f});
	highScoreText_1.SetText("HighScore 1: 0");

	auto highScoreText_2 = Tga::Text("Text/Ac437_IBM_CGA.ttf", Tga::FontSize_12);
	highScoreText_2.SetPosition(screenCenter + Tga::Vector2f{-400.0f, +120.0f});
	highScoreText_2.SetText("HighScore 2: 0");

	auto highScoreText_3 = Tga::Text("Text/Ac437_IBM_CGA.ttf", Tga::FontSize_12);
	highScoreText_3.SetPosition(screenCenter + Tga::Vector2f{-400.0f, 90.0f});
	highScoreText_3.SetText("HighScore 3: 0");

	auto pausedText = Tga::Text("Text/Ac437_IBM_CGA.ttf", Tga::FontSize_24);
	pausedText.SetPosition(screenCenter + Tga::Vector2f{-100.0f, -90.0f});
	pausedText.SetText("Paused");

	auto smartBombsText = Tga::Text("Text/Ac437_IBM_CGA.ttf", Tga::FontSize_14);
	smartBombsText.SetPosition(screenCenter + Tga::Vector2f{-300.0f, -300.0f});
	smartBombsText.SetText("SmartBombs 'S':");

	startButton->SetOnClickCallback([this]()
	{
		OnStartButtonClicked();
	});

	myTexts[TextId::Start] = startText;
	myTexts[TextId::Title] = titleText;
	myTexts[TextId::Instructions] = instructionsText;
	myTexts[TextId::Score] = scoreText;
	myTexts[TextId::GameOver] = gameOverText;
	myTexts[TextId::PlayAgain] = playAgain;
	myTexts[TextId::highScore_1] = highScoreText_1;
	myTexts[TextId::highScore_2] = highScoreText_2;
	myTexts[TextId::highScore_3] = highScoreText_3;
	myTexts[TextId::Paused] = pausedText;
	myTexts[TextId::BombCount] = smartBombsText;

	myButtons.push_back(std::move(startButton));
}

void UIManager::Update(float aDeltaTime, const Input* aInput)
{
	if (!aInput)
	{
		return;
	}

	Tga::Vector2f mousePos;
	mousePos.x = static_cast<float>(aInput->GetMouseAbsolutePOS().x);
	mousePos.y = static_cast<float>(myResolution.y - aInput->GetMouseAbsolutePOS().y);

	bool mouseClicked = aInput->IsKeyDown(KEY_LMB);
	//bool spacePressed = aInput->IsKeyPressed(KEY_SPACE);
	//bool pausePressed = aInput->IsKeyPressed('P');
	//myShowInstructions = aInput->IsKeyPressed('I');

	//if (pausePressed)
	//{
	//	//if (!myIsPaused)
	//	//{
	//	//	myGameState = GameState::Intro;
	//	//	myIsPaused = true;
	//	//	return;
	//	//}
	//	//else
	//	//{
	//	//	myGameState = GameState::InGame;
	//	//	myIsPaused = false;
	//	//	return;
	//	//}
	//}

	//if (spacePressed && (myGameState == GameState::Death || myGameState == GameState::Intro))
	//{
	//	if (!myIsPaused)
	//	{
	//		OnStartButtonClicked();
	//		return;
	//	}
	//}
	//	myIsPaused = false;
	//	myGameState = GameState::InGame;
	//}

	for (auto& button : myButtons)
	{
		button->Update(mousePos, mouseClicked);
	}

	if (myGameState == GameState::Death)
	{
		myDeathScreenDuration -= aDeltaTime;

		if (myDeathScreenDuration <= 0)
		{
			myGameState = GameState::Intro;
		}
	}

	myTexts[TextId::BombCount].SetText("SmartBombs 'S': " + std::to_string(mySmartBombs));
	myTexts[TextId::Score].SetText("Points: " + std::to_string(myBulletScore));

	if (myHighScores[0] > 0)
	{
		myTexts[TextId::highScore_1].SetText("HighScore 1: : " + std::to_string(myHighScores[0]));
	}
	if (myHighScores[1] > 0)
	{
		myTexts[TextId::highScore_2].SetText("HighScore 2: : " + std::to_string(myHighScores[1]));
	}
	if (myHighScores[2] > 0)
	{
		myTexts[TextId::highScore_3].SetText("HighScore 3: : " + std::to_string(myHighScores[2]));
	}

	UNREFERENCED_PARAMETER(aDeltaTime);
}

void UIManager::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	for (auto& button : myButtons)
	{
		button->Render();
	}

	if (myGameState == GameState::Intro)
	{
		myTexts[TextId::Start].Render(); //start 
		myTexts[TextId::Title].Render(); //gameTitle
		if (myShowInstructions)
		{
			myTexts[TextId::Instructions].Render(); //instr
		}

		myTexts[TextId::highScore_1].Render();
		myTexts[TextId::highScore_2].Render();
		myTexts[TextId::highScore_3].Render();
	}
	if (myGameState == GameState::InGame)
	{
		myTexts[TextId::Score].Render();
		myTexts[TextId::BombCount].Render();
	}
	if (myGameState == GameState::Death)
	{
		myTexts[TextId::GameOver].Render();
		myTexts[TextId::PlayAgain].Render();
	}
	if (myIsPaused)
	{
		myTexts[TextId::Paused].Render();
	}

	UNREFERENCED_PARAMETER(aSpriteDrawer);
}

void UIManager::LoseScore()
{
	myBulletScore--;
	if (myBulletScore <= 0)
	{
		myBulletScore = 0;
		myGameState = GameState::Restart;
	}
}

void UIManager::StartGame()
{
	if (myGameState == GameState::Death || myGameState == GameState::Intro)
	{
		if (!myIsPaused)
		{
			OnStartButtonClicked();
			return;
		}

		myIsPaused = false;
		myGameState = GameState::InGame;
	}
}

void UIManager::GameOver()
{
	CalculateHighScore();
	myGameState = GameState::Death;
}

void UIManager::RestartGame()
{
	mySmartBombs = 3;
	myBulletScore = 10;
	myDeathScreenDuration = 2.0f;
	myGameState = GameState::InGame;
}

void UIManager::PauseGame()
{
	if (!myIsPaused)
	{
		myGameState = GameState::Intro;
		myIsPaused = true;
		return;
	}

	StartGame();
}

void UIManager::ShowInstructions()
{
	if (myShowInstructions)
	{
		myShowInstructions = false;
		return;
	}
	myShowInstructions = true;
}

void UIManager::CalculateHighScore()
{
	for (int i = 0; i < std::size(myHighScores); ++i)
	{
		if (myHighScores[i] <= -1)
		{
			myHighScores[i] = myBulletScore;
			return;
		}
	}

	for (int i = std::size(myHighScores) - 1; i >= 0; --i)
	{
		myHighScores[i - 1] = myHighScores[i];
	}

	myHighScores[0] = myBulletScore;
}

void UIManager::SetOnStartGameCallback(std::function<void()> aCallback)
{
	myOnStartGameCallback = aCallback;
}

void UIManager::OnStartButtonClicked()
{
	// Fire the callback if set
	if (myOnStartGameCallback)
	{
		myOnStartGameCallback();
	}
	myButtons.clear();

	RestartGame();
}
