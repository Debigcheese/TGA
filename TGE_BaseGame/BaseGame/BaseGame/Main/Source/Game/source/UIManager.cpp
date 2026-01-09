#include "UIManager.h"
#include <tge/engine.h>

#include "Paratrooper.h"
#include "tge/error/ErrorManager.h"
#include "tge/graphics/GraphicsEngine.h"
#include "tge/text/TextService.h"
#include "tge/texture/TextureManager.h"
#include "JsonService.h"

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

	//Tga::Vector2f screenCenter = {
	//	static_cast<float>(myResolution.x) * 0.5f,
	//	static_cast<float>(myResolution.y) * 0.5f
	//};

	//auto startButton = std::make_unique<Button>();
	//startButton->SetPosition(screenCenter + Tga::Vector2f{30.0f, -90.0f});
	//startButton->SetSize({150.0f, 45.0f});
	//startButton->SetTexture("Sprites/Button.png");
	//startButton->SetOnClickCallback([this]()
	//{
	//	OnStartButtonClicked();
	//});

	//myButtons.push_back(std::move(startButton));

	InitTextData();
}

void UIManager::InitTextData()
{
	auto& cfg = JsonService::Get();
	auto& texts = cfg["Texts"];

	myTexts.resize(texts.size());

	for (size_t i = 0; i < texts.size(); ++i)
	{
		const auto& tCfg = texts[i];

		std::string id = tCfg["uniqueId"].get<std::string>();
		std::string visibility = tCfg["visibleWhen"].get<std::string>();
		std::string text = tCfg["text"].get<std::string>();
		float posX = tCfg["posX"].get<float>();
		float posY = tCfg["posY"].get<float>();
		int size = tCfg["size"].get<int>();
		std::string fontPath = tCfg["fontPath"].get<std::string>();

		myTexts[i].uniqueId = id;
		SetTextVisibility(myTexts[i], visibility);
		myTexts[i].text = {fontPath.c_str(), static_cast<Tga::FontSize>(size)};
		myTexts[i].text.SetText(text);
		myTexts[i].text.SetPosition(Tga::Vector2f{posX, posY} * static_cast<Tga::Vector2f>(myResolution));
	}
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
	bool spacePressed = aInput->IsKeyPressed(KEY_SPACE);
	bool escapePressed = aInput->IsKeyPressed(KEY_ESCAPE);
	bool pausePressed = aInput->IsKeyPressed('P');
	bool showInstructions = aInput->IsKeyPressed('I');

	if (escapePressed)
	{
		Tga::Engine& engine = *Tga::Engine::GetInstance();
		engine.Shutdown(); // dont know any better way 
	}

	if (spacePressed)
	{
		StartGame();
	}

	if (pausePressed)
	{
		PauseGame();
	}

	if (showInstructions)
	{
		ShowInstructions();
	}

	UpdateUsernameInput(aInput);

	if (myIsEnteringUsername)
	{
		return;
	}

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

	GetText("BombCount").SetText("SmartBombs 'S': " + std::to_string(mySmartBombs));
	GetText("Score").SetText("Points: " + std::to_string(myBulletScore));

	if (myHighScores[0] > 0)
	{
		GetText("highScore_1").SetText("HighScore 1: : " + std::to_string(myHighScores[0]));
	}
	if (myHighScores[1] > 0)
	{
		GetText("highScore_2").SetText("HighScore 2: : " + std::to_string(myHighScores[1]));
	}
	if (myHighScores[2] > 0)
	{
		GetText("highScore_3").SetText("HighScore 3: : " + std::to_string(myHighScores[2]));
	}

	UNREFERENCED_PARAMETER(aDeltaTime);
}

void UIManager::UpdateUsernameInput(const Input* aInput)
{
	if (!myIsEnteringUsername)
	{
		return;
	}

	char character = aInput->GetPressedCharacter();
	if (character != '\0' && myUserName.length() < 10)
	{
		myUserName += character;
	}

	if (aInput->IsKeyPressed(KEY_BACKSPACE) && !myUserName.empty())
	{
		myUserName.pop_back();
	}

	GetText("Username").SetText("Enter your username\n"
		"		Username: " + myUserName);

	if (aInput->IsKeyPressed(KEY_ENTER) && !myUserName.empty())
	{
		SubmitName();
	}
}

void UIManager::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	for (auto& button : myButtons)
	{
		button->Render();
	}

	for (auto& UIText : myTexts)
	{
		if (ShouldRender(UIText.textVisibility))
		{
			UIText.text.Render();
		}
	}

	UNREFERENCED_PARAMETER(aSpriteDrawer);
}

Tga::Text& UIManager::GetText(const std::string& aUniqueId)
{
	for (auto& text : myTexts)
	{
		if (text.uniqueId == aUniqueId)
		{
			return text.text;
		}
	}
	//assert(false && "Error in HUD: Text ID not found");
	return myTexts.front().text;
}

void UIManager::SetTextVisibility(UIText& aText, const std::string& aVisibility)
{
	if (aVisibility == "Intro")
	{
		aText.textVisibility = TextVisibility::Intro;
	}
	else if (aVisibility == "InGame")
	{
		aText.textVisibility = TextVisibility::InGame;
	}
	else if (aVisibility == "GameOver")
	{
		aText.textVisibility = TextVisibility::GameOver;
	}
	else if (aVisibility == "Restart")
	{
		aText.textVisibility = TextVisibility::Restart;
	}
	else if (aVisibility == "Instructions")
	{
		aText.textVisibility = TextVisibility::Instructions;
	}
	else if (aVisibility == "Paused")
	{
		aText.textVisibility = TextVisibility::Paused;
	}
	else
	{
		aText.textVisibility = TextVisibility::Always;
	}
}

bool UIManager::ShouldRender(TextVisibility aTextVisibility) const
{
	switch (aTextVisibility)
	{
		case TextVisibility::Intro:
		{
			return myGameState == GameState::Intro;
		}
		case TextVisibility::InGame:
		{
			return myGameState == GameState::InGame;
		}
		case TextVisibility::GameOver:
		{
			return myGameState == GameState::Death;
		}
		case TextVisibility::Restart:
		{
			return myGameState == GameState::Restart;
		}
		case TextVisibility::Instructions:
		{
			return myShowInstructions;
		}
		case TextVisibility::Paused:
		{
			return myIsPaused;
		}
		case TextVisibility::Always:
		{
			return true;
		}
	}
	return true;
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
	if (myGameState == GameState::Intro && !myIsPaused)
	{
		return;
	}
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
	if (myIsEnteringUsername)
	{
		return;
	}
	myShowInstructions = myShowInstructions ? !myShowInstructions : true;
}

void UIManager::SubmitName()
{
	myIsEnteringUsername = false;

	GetText("Username").SetPosition(Tga::Vector2f{145.0f, myResolution.y - 150.0f});
	GetText("Username").SetText("Username: " + myUserName);
}

void UIManager::CalculateHighScore()
{
	int index = -1;

	for (int i = 0; i < myHighScores.size(); ++i)
	{
		if (myBulletScore >= myHighScores[i])
		{
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		return;
	}

	for (int i = (int)myHighScores.size() - 1; i > 0; --i)
	{
		myHighScores[i] = myHighScores[i - 1];
	}
	myHighScores[index] = myBulletScore;
}

void UIManager::SetOnStartGameCallback(std::function<void()> aCallback)
{
	myOnStartGameCallback = aCallback;
}

void UIManager::OnStartButtonClicked()
{
	if (myIsEnteringUsername)
	{
		return;
	}
	// Fire the callback if set
	if (myOnStartGameCallback)
	{
		myOnStartGameCallback();
	}
	myButtons.clear();

	RestartGame();
}
