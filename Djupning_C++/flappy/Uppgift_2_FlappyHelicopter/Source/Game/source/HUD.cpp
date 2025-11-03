#include "HUD.h"

#include "CommonUtilities/UtilityFunctions.h"
#include "tge/shaders/SpriteShader.h"
#include "tge/text/TextService.h"

HUD::HUD()
{
}

HUD::~HUD()
{
}

void HUD::Init(Tga::Engine& aEngine)
{
	//Get resolution
	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};

	InitTextData();

	// Create a new shader
	myShader.Init("shaders/instanced_sprite_shader_VS", "shaders/custom_sprite_pixel_shader_PS");
}

void HUD::InitTextData()
{
	myScoreStr = "0";
	myEnemyScoreStr = "0";

	myScoreTx = {"Text/arial.ttf", Tga::FontSize_36};
	myScoreTx.SetText("");
	myScoreTx.SetPosition(Tga::Vector2f{0.49f, 0.82f} * myScreenResolution);
	myScoreLerpData.defaultValue = myScoreTx.GetScale();

	myIntroText = {"Text/arial.ttf", Tga::FontSize_36};
	myIntroText.SetText("Ping Pong");
	myIntroText.SetPosition(Tga::Vector2f{0.47f, 0.90f} * myScreenResolution);

	myPressStartText = {"Text/arial.ttf", Tga::FontSize_24};
	myPressStartText.SetText("Press 'Enter' to Start");
	myPressStartText.SetPosition(Tga::Vector2f{0.45f, 0.15f} * myScreenResolution);

	myRestartText = {"Text/arial.ttf", Tga::FontSize_24};
	myRestartText.SetText("Press 'Enter' to Restart");
	myRestartText.SetPosition(Tga::Vector2f{0.425f, 0.15f} * myScreenResolution);

	auto& text = myGameOverData.myGameOverText;
	const auto str = myGameOverData.myGameOverStr;

	text = {"Text/arial.ttf", Tga::FontSize_60};
	text.SetText("");
	text.SetPosition(Tga::Vector2f{0.4f, 0.5f} * myScreenResolution);
}

void HUD::Render()
{
	myScoreTx.Render();

	if (myShowFinish)
	{
		myGameOverData.myGameOverText.Render();
	}

	if (myShowIntro)
	{
		myIntroText.Render();
		myPressStartText.Render();
	}

	if (myShowRestart)
	{
		myRestartText.Render();
	}
}

void HUD::Update(float aTimeDelta, GameState& aGameState)
{
	int playerScore = aGameState.GetScore(Actor::Player);
	int enemyScore = aGameState.GetScore(Actor::Enemy);

	myScoreStr = std::to_string(playerScore);
	myEnemyScoreStr = std::to_string(enemyScore);

	myScoreTx.SetText(myScoreStr + " - " + myEnemyScoreStr);

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
