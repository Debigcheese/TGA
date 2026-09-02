#include "GameWorld.h"

#include <tge/graphics/GraphicsEngine.h>
#include <tge/graphics/dx11.h>

#include <tge/drawers/SpriteDrawer.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/DebugDrawer.h>
#include <tge/engine.h>
#include "UpdateContext.h"
#include <tge/input/InputManager.h>


using namespace Tga;

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
}
void GameWorld::Init()
{
    // Get the singleton
    AI::PollingStation& pollingStation =
        AI::PollingStation::GetInstance();

    auto player = std::make_unique<Actor>();

    player->Init(
        "../data/sprites/hacker.png",
        0.2f,
        myControllerFactory.CreateController(AI::eControllerType::ePlayer),
        { 0.f, 0.5f }
    );
    myPlayer = player.get();

    auto pc1 = std::make_unique<Actor>();
    auto pc2 = std::make_unique<Actor>();
    auto pc3 = std::make_unique<Actor>();

    myPC1Pos = { computer1.min.x + (computer1.max.x - computer1.min.x) / 2 - .03f, computer1.max.y + (computer1.max.y - computer1.min.y) / 2 - .1f };
    myPC2Pos = { computer2.min.x + (computer2.max.x - computer2.min.x) / 2 - .03f, computer2.max.y + (computer2.max.y - computer2.min.y) / 2 - .1f };
    myPC3Pos = { computer3.min.x + (computer3.max.x - computer3.min.x) / 2 - .03f, computer3.max.y + (computer3.max.y - computer3.min.y) / 2 - .1f };

    pc1->Init(
        "../data/sprites/Computer.png",
        0.0f,
        nullptr,
        myPC1Pos
    );

    pc2->Init(
        "../data/sprites/Computer.png",
        0.0f,
        nullptr,
        myPC2Pos
    );

    pc3->Init(
        "../data/sprites/Computer.png",
        0.0f,
        nullptr,
        myPC3Pos
    );

    pollingStation.Init(myPlayer, pc1.get(), pc2.get(), pc3.get());

    myActors.push_back(std::move(player));

    myActors.push_back(std::move(pc1));
    myActors.push_back(std::move(pc2));
    myActors.push_back(std::move(pc3));

    myControllerFactory.Init(&pollingStation);

    auto enemy1 = std::make_unique<Actor>();
    auto enemy2 = std::make_unique<Actor>();
    auto enemy3 = std::make_unique<Actor>();
    auto enemy4 = std::make_unique<Actor>();

    enemy1->Init(
        "../data/sprites/killerRobo1.png",
        0.10f,
        myControllerFactory.CreateController(AI::eControllerType::ePolling),
        { .3f, .3f }
    );

    enemy2->Init(
        "../data/sprites/killerRobo1.png",
        0.12f,
        myControllerFactory.CreateController(AI::eControllerType::ePolling),
        { .35f, .5f }
    );

    enemy3->Init(
        "../data/sprites/killerRobo2.png",
        0.14f,
        myControllerFactory.CreateController(AI::eControllerType::eEvent),
        { .7f, .7f }
    );

    enemy4->Init(
        "../data/sprites/killerRobo2.png",
        0.16f,
        myControllerFactory.CreateController(AI::eControllerType::eEvent),
        { .8f, .3f }
    );

    auto eventManager = AIEventManager::GetInstance();

    eventManager.Subscribe(enemy3.get()->GetController());
    eventManager.Subscribe(enemy4.get()->GetController());

    myActors.push_back(std::move(enemy1));
    myActors.push_back(std::move(enemy2));
    myActors.push_back(std::move(enemy3));
    myActors.push_back(std::move(enemy4));
}


void GameWorld::Update(const UpdateContext& context)
{
	for (auto& actor : myActors)
	{
		actor->Update(context);
	}
    auto playerPosition = myPlayer->GetPosition();

    if (computer1.Contains(playerPosition))
    {
        AI::PollingStation::GetInstance().SetPlayerOnComputer(PlayerOnPC::PC1);
        myCurrentComputer = PlayerOnPC::PC1;
    }
    else if (computer2.Contains(playerPosition))
    {
        AI::PollingStation::GetInstance().SetPlayerOnComputer(PlayerOnPC::PC2);
        myCurrentComputer = PlayerOnPC::PC2;
    }
    else if (computer3.Contains(playerPosition))
    {
        AI::PollingStation::GetInstance().SetPlayerOnComputer(PlayerOnPC::PC3);
        myCurrentComputer = PlayerOnPC::PC3;
    }
    else
    {
        AI::PollingStation::GetInstance().SetPlayerOnComputer(PlayerOnPC::None);
        myCurrentComputer = PlayerOnPC::None;
    }

    if(myCurrentComputer != PlayerOnPC::None && myCurrentComputer != myPreviousComputer)
    {
        AIEvent event;
        event.myType = AIEvent::Type::ComputerActivated;

        switch(myCurrentComputer)
        {
            case PlayerOnPC::PC1:
            {
                event.myPosition = myPC1Pos;
                break;
            }
            case PlayerOnPC::PC2:
            {
                event.myPosition = myPC2Pos;
                break;
            }
            case PlayerOnPC::PC3:
            {
                event.myPosition = myPC3Pos;
                break;
            }
        }
        AIEventManager::GetInstance().SendEvent(event);
        myPreviousComputer = myCurrentComputer;
    }

}

void GameWorld::Render()
{
	auto& engine = *Tga::Engine::GetInstance();

	Tga::Vector2f resolution = Tga::Vector2f((float)Tga::DX11::GetResolution().x, (float)Tga::DX11::GetResolution().y);
	myScreenMin = { 0.f, 0.f };
	myScreenMax = {1.0f , 1.0f };

	camera.SetOrtographicProjection(myScreenMin.x, myScreenMax.x, myScreenMin.y, myScreenMax.y, -1.0f, 1.0f);
	engine.GetGraphicsEngine().GetGraphicsStateStack().SetCamera(camera);


	Tga::SpriteDrawer& spriteDrawer(engine.GetGraphicsEngine().GetSpriteDrawer());

	{
		Tga::SpriteSharedData sharedData = {};
		sharedData.myTexture = myBackgroundTexture;

		Tga::Sprite2DInstanceData instanceData = {};
		instanceData.myPivot = { 0.0f, 1.0f };
		instanceData.myPosition = { 0.0f, 0.0f };
		instanceData.mySize = { 1.0f, 1.0f };

		spriteDrawer.Draw(sharedData, instanceData);
	}
	for (auto& actor : myActors)
	{
		actor->Render();
	}
}