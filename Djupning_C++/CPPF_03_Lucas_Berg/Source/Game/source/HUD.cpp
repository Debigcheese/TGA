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
	//Get resolution
	Tga::Vector2ui intResolution = aEngine.GetRenderSize();
	myScreenResolution = {static_cast<float>(intResolution.x), static_cast<float>(intResolution.y)};

	InitSpriteData(aEngine);
	InitTextData();

	// Create a new shader
	myShader.Init("shaders/instanced_sprite_shader_VS", "shaders/custom_sprite_pixel_shader_PS");
}

void HUD::InitSpriteData(Tga::Engine& aEngine)
{
	auto& cfg = Config::Get();
	auto& sprites = cfg["Sprites"];

	mySprite.resize(sprites.size());

	for (size_t i = 0; i < sprites.size(); ++i)
	{
		const auto& sCfg = sprites[i];

		std::string path = sCfg["path"].get<std::string>();
		float posX = sCfg["posX"].get<float>();
		float posY = sCfg["posY"].get<float>();

		mySprite[i].sharedData.myTexture = aEngine.GetTextureManager().GetTexture(path.c_str());

		mySprite[i].instance.myPosition.x = posX * myScreenResolution.x;
		mySprite[i].instance.myPosition.y = posY * myScreenResolution.y;

		mySprite[i].instance.myPivot = {0.5f, 0.5f};
		mySprite[i].instance.myColor = Tga::Color(1.f, 1.f, 1.f, 1.f);
		mySprite[i].instance.mySize = mySprite[i].sharedData.myTexture->CalculateTextureSize();
		mySprite[i].instance.mySizeMultiplier = 1.0f;
	}
	mySprite[0].instance.mySizeMultiplier.x = 1.15f;
}

void HUD::InitTextData()
{
	auto& cfg = Config::Get();
	auto& texts = cfg["Texts"];

	myTexts.resize(texts.size());

	for (size_t i = 0; i < texts.size(); ++i)
	{
		const auto& tCfg = texts[i];

		std::string id = tCfg["id"].get<std::string>();
		std::string text = tCfg["text"].get<std::string>();
		float posX = tCfg["posX"].get<float>();
		float posY = tCfg["posY"].get<float>();
		int size = tCfg["size"].get<int>();

		myTexts[i] = {"Text/BoldPixels.ttf", static_cast<Tga::FontSize>(size)};
		myTexts[i].SetText(text);
		myTexts[i].SetPosition(Tga::Vector2f{posX, posY} * myScreenResolution);
	}
}

void HUD::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	myTexts[3].Render();

	if (myShowFinish)
	{
		myTexts[4].Render();
	}

	if (myShowIntro)
	{
		for (const auto& sprite : mySprite)
		{
			aSpriteDrawer.Draw(sprite.sharedData, sprite.instance);
		}

		for (int i = 0; i < myTexts.size(); ++i)
		{
			if (i > 1 && i < 5)
			{
				return;
			}
			myTexts[i].Render();
		}
	}

	if (myShowRestart)
	{
		myTexts[2].Render();
	}
}

void HUD::Update(const GameState& aGameState)
{
	int playerScore = aGameState.GetScore();

	std::string scoreStr = std::to_string(playerScore);

	myTexts[3].SetText(scoreStr);
}

Tga::Text HUD::GetText()
{
	return myTexts[3];
}
