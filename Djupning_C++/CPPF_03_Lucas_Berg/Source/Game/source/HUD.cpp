#include "HUD.h"

#include "Config.h"
#include "CommonUtilities/UtilityFunctions.h"
#include "tge/drawers/SpriteDrawer.h"
#include "tge/shaders/SpriteShader.h"
#include "tge/text/TextService.h"
#include "tge/texture/TextureManager.h"

#include "nlohmann/json.hpp"

HUD::HUD()
{
}

HUD::~HUD()
{
}

void HUD::Init(Tga::Engine& aEngine)
{
	std::string titleText = Config::Get()["TitleText"]["text"];
	float titlePosX = Config::Get()["TitleText"]["posX"];
	float titlePosY = Config::Get()["TitleText"]["posY"];

	myIntroTextPos = Tga::Vector2f{titlePosX, titlePosY};

	std::string titleBorderText = Config::Get()["TitleBorder"]["path"];
	float titleBorderPosX = Config::Get()["TitleBorder"]["posX"];
	float titleBorderPosY = Config::Get()["TitleBorder"]["posY"];

	std::cout << titleBorderPosX;

	//Get resolution
	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};

	myTitleBorderTexture = aEngine.GetTextureManager().GetTexture(titleBorderText.c_str());
	mySprite.sharedData.myTexture = myTitleBorderTexture;

	mySprite.instance.myPosition.x = titleBorderPosX * myScreenResolution.x;
	mySprite.instance.myPosition.y = titleBorderPosY * myScreenResolution.y;

	mySprite.instance.myPivot = {0.5f, 0.5f};
	mySprite.instance.myColor = Tga::Color(1.0f, 1.0f, 1.0f, 1.0f);
	mySprite.instance.mySize = mySprite.sharedData.myTexture->CalculateTextureSize(); // Tga::Vector2ui{5, 5};
	mySprite.instance.mySizeMultiplier = 1.0f;

	InitTextData();

	// Create a new shader
	myShader.Init("shaders/instanced_sprite_shader_VS", "shaders/custom_sprite_pixel_shader_PS");
}

void HUD::InitTextData()
{
	myScoreStr = "0";

	myScoreTx = {"Text/BoldPixels.ttf", Tga::FontSize_36};

	myScoreTx.SetText("");
	myScoreTx.SetPosition(Tga::Vector2f{0.49f, 0.82f} * myScreenResolution);
	myScoreLerpData.defaultValue = myScoreTx.GetScale();

	myIntroText = {"Text/BoldPixels.ttf", Tga::FontSize_36};
	myIntroText.SetText("Flappy Helicopter");
	myIntroText.SetPosition(Tga::Vector2f{0.42f, 0.90f} * myScreenResolution);
	myIntroText.SetColor(Tga::Color(1.0f, 0.5f, 0.5f, 1.0f));

	myPressStartText = {"Text/BoldPixels.ttf", Tga::FontSize_24};
	myPressStartText.SetText("Press 'Enter' to Start");
	myPressStartText.SetPosition(Tga::Vector2f{0.45f, 0.15f} * myScreenResolution);

	myRestartText = {"Text/BoldPixels.ttf", Tga::FontSize_24};
	myRestartText.SetText("Press 'Enter' to Restart");
	myRestartText.SetPosition(Tga::Vector2f{0.425f, 0.15f} * myScreenResolution);

	auto& text = myGameOverData.myGameOverText;
	const auto str = myGameOverData.myGameOverStr;

	text = {"Text/BoldPixels.ttf", Tga::FontSize_60};
	text.SetText("");
	text.SetPosition(Tga::Vector2f{0.4f, 0.5f} * myScreenResolution);
}

void HUD::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	myScoreTx.Render();

	if (myShowFinish)
	{
		myGameOverData.myGameOverText.Render();
	}

	if (myShowIntro)
	{
		aSpriteDrawer.Draw(mySprite.sharedData, mySprite.instance);
		myIntroText.Render();
		myPressStartText.Render();
	}

	if (myShowRestart)
	{
		myRestartText.Render();
	}
}

void HUD::Update(float aTimeDelta, const GameState& aGameState)
{
	int playerScore = aGameState.GetScore();

	myScoreStr = std::to_string(playerScore);

	myScoreTx.SetText(myScoreStr);

	if (myScoreLerpData.isLerping && myScoreLerpData.timer <= myScoreLerpData.duration)
	{
		auto& data = myScoreLerpData;
		data.timer += aTimeDelta;

		data.lerpValue = CommonUtilities::Lerp(data.current, data.target, data.timer);
		myScoreTx.SetScale(data.lerpValue);
	}
	else
	{
		myScoreLerpData.isLerping = false;
		LerpTextSize(myScoreLerpData.defaultValue, 0.25f);
	}
}

Tga::Text HUD::GetText()
{
	return myScoreTx;
}

void HUD::LerpTextSize(float aSize, float aDuration)
{
	auto& data = myScoreLerpData;

	data.target = aSize;
	data.duration = aDuration;
	data.current = myScoreTx.GetScale();
	data.timer = 0.0f;
	data.isLerping = true;
}

void HUD::SetGameOverStr(const std::string& aString)
{
	myGameOverData.myGameOverStr = aString;
	myGameOverData.myGameOverText.SetText(aString);
}
