#pragma once

class Game;

class IMapGenerationStrategy
{
public:
    virtual ~IMapGenerationStrategy() {}
    virtual void Generate(Game* game) = 0;
};
