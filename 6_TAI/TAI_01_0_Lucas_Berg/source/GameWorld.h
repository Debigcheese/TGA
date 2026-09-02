#pragma once

#include <vector>
#include <tge/sprite/sprite.h>
#include <tge/graphics/Camera.h>
#include "Actor.h"
#include "Controller.h"
#include "PollingStation.h"
#include "AIEventManager.h"

namespace Tga
{
	class Texture;
}
class GameWorld
{
public:

struct AABB
{
    Tga::Vector2f min;
    Tga::Vector2f max;

    bool Contains(const Tga::Vector2f& aPosition) const
    {
        return aPosition.x >= min.x &&
               aPosition.x <= max.x &&
               aPosition.y >= min.y &&
               aPosition.y <= max.y;
    }
};

	GameWorld(); 
	~GameWorld();

	void Init();
	void Update(const UpdateContext& inputContext);
	
	void Render();
	Tga::Vector2f GetScreenMin() { return myScreenMin; };
	Tga::Vector2f GetScreenMax() { return myScreenMax; };
private:
	Actor* myPlayer;
	std::vector<std::unique_ptr<Actor>> myActors;
	std::unique_ptr<AI::PollingStation> myPollingStation;
	AI::ControllerFactory myControllerFactory;
	AIEventManager myAIEventManager;
	Tga::Texture* myBackgroundTexture;

	Tga::Vector2f myScreenMin;
	Tga::Vector2f myScreenMax;
	Tga::Camera camera;

	PlayerOnPC myCurrentComputer;
	PlayerOnPC myPreviousComputer;

	Tga::Vector2f myPC1Pos;
	Tga::Vector2f myPC2Pos;
	Tga::Vector2f myPC3Pos;

	AABB computer1 =
{
    { 0.4f, 0.3f },
    { 0.5f, 0.4f }
};

AABB computer2 =
{
    { 0.7f, 0.6f },
    { 0.8f, 0.7f }
};

AABB computer3 =
{
    { 0.1f, 0.7f },
    { 0.2f, 0.8f }
};

};