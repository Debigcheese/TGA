#pragma once

class Game;

class IMapPass
{
public:
    virtual ~IMapPass() {}
    virtual void Execute(Game* game) = 0;
};
