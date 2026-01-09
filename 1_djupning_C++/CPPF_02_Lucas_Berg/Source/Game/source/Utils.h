#pragma once
#include "Config.h"
#include "tge/Engine.h"

namespace Utils
{
	Tga::TextureResource* GetTextureFromPath(const Tga::Engine& aEngine, std::string aTexturePath);
}
