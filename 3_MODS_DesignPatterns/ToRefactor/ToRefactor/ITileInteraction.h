#pragma once

class Game;
class Actor;

class ITileInteraction
{
public:
    virtual ~ITileInteraction() {}
    virtual void OnStep(Game* game, Actor* actor) = 0;
};
