#include "Utils.h"
#include "tge/texture/TextureManager.h"

namespace Utils
{
	Tga::TextureResource* GetTextureFromPath(const Tga::Engine& aEngine, std::string aTexturePath)
	{
		return aEngine.GetTextureManager().GetTexture(aTexturePath.c_str());
	}
}
