#pragma once
#include "Ship.h"

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void Init();
	void Update(float aTimeDelta);
	void Render() const;

private:
	Ship* myShip;
};
