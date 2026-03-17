#pragma once

#include <string>
#include "IMessageListener.h"

class Game;
class Spell;
class Actor;

class GameState
{
public:
    virtual ~GameState() {}
    virtual void Update(Game* game) = 0;
    virtual void Draw(Game* game) = 0;
};

class GameOverState : public GameState
{
public:
    void Update(Game* game) override;
    void Draw(Game* game) override;
};

class PlayState : public GameState, public IMessageListener
{
private:
    Game* myGame;
public:
    PlayState(Game* game);
    ~PlayState() {}
    void HandleMessage(Message* msg) override;
    void Update(Game* game) override;
    void Draw(Game* game) override;
};

class TargetState : public GameState
{
public:
    GameState* myPreviousState;
    int myTargetX;
    int myTargetY;
    Spell* mySpell;
    Actor* myCaster;
    TargetState(Game* game, GameState* prev);
    void Update(Game* game) override;
    void Draw(Game* game) override;
};

class MessageState : public GameState
{
public:
    GameState* myPreviousState;
    std::string myMessage;
    MessageState(GameState* prev, std::string msg);
    void Update(Game* game) override;
    void Draw(Game* game) override;
};

class HelpState : public MessageState
{
public:
    HelpState(GameState* prev, std::string msg) : MessageState(prev, msg) {}
    void Draw(Game* game) override;
};
