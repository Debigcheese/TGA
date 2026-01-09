#pragma once
#include <functional>
#include <tge/math/vector2.h>
#include "tge/drawers/SpriteDrawer.h"
#include "tge/sprite/sprite.h"

namespace Tga
{
	class TextureResource;
	class SpriteBatchScope;
}

class Button
{
public:
	Button();
	~Button();

	void SetPosition(const Tga::Vector2f& aPosition) { mySpriteInstance.myPosition = aPosition; }
	void SetSize(const Tga::Vector2f& aSize) { mySpriteInstance.mySize = aSize; }
	void SetTexture(const char* aTexturePath);
	void SetHoverTexture(const char* aTexturePath);
	void SetPressedTexture(const char* aTexturePath);

	void SetOnClickCallback(std::function<void()> aCallback);

	void Update(const Tga::Vector2f& aMousePosition, bool aMouseClicked);
	void Render();

	bool IsHovered() const { return myIsHovered; }
	bool IsPressed() const { return myIsPressed; }

	const Tga::Vector2f& GetPosition() const { return mySpriteInstance.myPosition; }

private:
	bool IsPointInside(const Tga::Vector2f& aPoint) const;
	const Tga::TextureResource* GetCurrentTexture() const;

	const Tga::TextureResource* myNormalTexture = nullptr;
	const Tga::TextureResource* myHoverTexture = nullptr;
	const Tga::TextureResource* myPressedTexture = nullptr;

	Tga::Sprite2DInstanceData mySpriteInstance;

	bool myIsHovered = false;
	bool myIsPressed = false;
	bool myWasPressed = false;

	std::function<void()> myOnClickCallback;
};
