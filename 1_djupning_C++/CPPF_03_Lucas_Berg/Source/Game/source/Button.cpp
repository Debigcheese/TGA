#include "Button.h"
#include <tge/engine.h>
#include <tge/texture/TextureManager.h>
#include <tge/sprite/sprite.h>

#include "tge/drawers/SpriteDrawer.h"
#include "tge/error/ErrorManager.h"
#include "tge/graphics/GraphicsEngine.h"

Button::Button()
{
	mySpriteInstance.myPivot = {0.5f, 0.5f};
}

Button::~Button()
{
}

void Button::SetTexture(const char* aTexturePath)
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();
	myNormalTexture = engine.GetTextureManager().GetTexture(aTexturePath);

	Tga::Vector2f size = mySpriteInstance.mySize;

	if (size.x == 0.0f && size.y == 0.0f)
	{
		size = myNormalTexture->CalculateTextureSize();
		mySpriteInstance.mySize = size;
	}
}

void Button::SetHoverTexture(const char* aTexturePath)
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();
	myHoverTexture = engine.GetTextureManager().GetTexture(aTexturePath);
}

void Button::SetPressedTexture(const char* aTexturePath)
{
	Tga::Engine& engine = *Tga::Engine::GetInstance();
	myPressedTexture = engine.GetTextureManager().GetTexture(aTexturePath);
}

void Button::SetOnClickCallback(std::function<void()> aCallback)
{
	myOnClickCallback = aCallback;
}

void Button::Update(const Tga::Vector2f& aMousePosition, bool aMouseClicked)
{
	myIsHovered = IsPointInside(aMousePosition);

	if (myIsHovered && aMouseClicked)
	{
		myIsPressed = true;
	}
	else
	{
		myIsPressed = false;
	}

	if (myWasPressed && !aMouseClicked && myIsHovered)
	{
		if (myOnClickCallback)
		{
			myOnClickCallback();
		}
	}

	myWasPressed = aMouseClicked && myIsHovered;
}

void Button::Render()
{
	Tga::SpriteSharedData sharedData;
	sharedData.myTexture = GetCurrentTexture();

	auto& spriteDrawer = Tga::Engine::GetInstance()->GetGraphicsEngine().GetSpriteDrawer();
	Tga::SpriteBatchScope batch = spriteDrawer.BeginBatch(sharedData);

	batch.Draw(mySpriteInstance);
}

const Tga::TextureResource* Button::GetCurrentTexture() const
{
	if (myIsPressed && myPressedTexture)
	{
		return myPressedTexture;
	}
	else if (myIsHovered && myHoverTexture)
	{
		return myHoverTexture;
	}

	return myNormalTexture;
}

bool Button::IsPointInside(const Tga::Vector2f& aPoint) const
{
	Tga::Vector2f size = mySpriteInstance.mySize;
	float halfWidth = size.x * 0.5f;
	float halfHeight = size.y * 0.5f;

	Tga::Vector2f position = mySpriteInstance.myPosition;
	return aPoint.x >= position.x - halfWidth &&
		aPoint.x <= position.x + halfWidth &&
		aPoint.y >= position.y - halfHeight &&
		aPoint.y <= position.y + halfHeight;
}
