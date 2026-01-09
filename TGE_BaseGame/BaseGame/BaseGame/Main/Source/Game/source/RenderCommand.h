#pragma once
#include "tge/sprite/sprite.h"
#include <vector>

struct RenderCommandData
{
	const Tga::TextureResource* myTexture;
	Tga::Sprite2DInstanceData myInstanceData;
};

class RenderCommand
{
public:
	RenderCommand();

	void AddSprite(const Tga::Sprite2DInstanceData& aInstanceData, const Tga::SpriteSharedData& aSharedData) const;
	void Execute() const;
	void Swap() const;

private:
	mutable std::vector<RenderCommandData> myCommandsQueue[2];
	mutable int myWriteBuffer = 0;
	mutable int myReadBuffer = 1;
};
