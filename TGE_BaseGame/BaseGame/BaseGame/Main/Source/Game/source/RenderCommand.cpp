#include "RenderCommand.h"

#include "tge/Engine.h"
#include "tge/drawers/SpriteDrawer.h"
#include "tge/graphics/GraphicsEngine.h"

RenderCommand::RenderCommand()
{
}

void RenderCommand::AddSprite(
	const Tga::Sprite2DInstanceData& aInstanceData,
	const Tga::SpriteSharedData& aSharedData) const
{
	RenderCommandData cmd;
	cmd.myTexture = aSharedData.myTexture;
	cmd.myInstanceData = aInstanceData;

	myCommandsQueue[myWriteBuffer].push_back(cmd);
}

void RenderCommand::Execute() const
{
	const std::vector<RenderCommandData>& commands = myCommandsQueue[myReadBuffer];

	if (!commands.empty())
	{
		auto& spriteDrawer = Tga::Engine::GetInstance()->GetGraphicsEngine().GetSpriteDrawer();

		const Tga::TextureResource* currentTexture = nullptr;
		std::vector<Tga::Sprite2DInstanceData> batch;

		for (const auto& cmd : commands)
		{
			if (cmd.myTexture != currentTexture && !batch.empty())
			{
				Tga::SpriteSharedData sharedData;
				sharedData.myTexture = currentTexture;

				Tga::SpriteBatchScope scope = spriteDrawer.BeginBatch(sharedData);
				scope.Draw(batch.data(), batch.size());

				batch.clear();
			}

			currentTexture = cmd.myTexture;
			batch.push_back(cmd.myInstanceData);
		}

		if (!batch.empty())
		{
			Tga::SpriteSharedData sharedData;
			sharedData.myTexture = currentTexture;

			Tga::SpriteBatchScope scope = spriteDrawer.BeginBatch(sharedData);
			scope.Draw(batch.data(), batch.size());
		}
	}
}

void RenderCommand::Swap() const
{
	myCommandsQueue[myReadBuffer].clear();
	std::swap(myReadBuffer, myWriteBuffer);
}
