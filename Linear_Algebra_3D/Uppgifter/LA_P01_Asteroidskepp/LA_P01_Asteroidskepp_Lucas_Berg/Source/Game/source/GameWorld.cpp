#include "GameWorld.h"

using namespace Tga;

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
}

void GameWorld::Init()
{
	myShip = new Ship();
}

void GameWorld::Update(float aTimeDelta)
{
	myShip->Update(aTimeDelta);
}

void GameWorld::Render() const
{
	myShip->Render();
}
