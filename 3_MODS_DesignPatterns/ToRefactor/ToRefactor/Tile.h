#pragma once
#include "ITileInteraction.h"
#include "LogMessage.h"
#include "MessageBus.h"

class Tile : public ITileInteraction
{
public:
    Tile(char s) : m_symbol(s), m_isDiscovered(false) {}
    virtual ~Tile() {}

    void OnStep(Game* game, Actor* actor) override
    {
        SetDiscovered(true);
    }

    virtual bool IsWalkable(Actor* actor) { return false; }

    char GetTileSymbol() const { return m_symbol; }
    bool WasDiscovered() const { return m_isDiscovered; }

    void SetDiscovered(bool d) { m_isDiscovered = d; }

private:
    char m_symbol;
    bool m_isDiscovered;
};

class FloorTile : public Tile
{
public:
#define FLOOR_SYMBOL '.'
    FloorTile() : Tile(FLOOR_SYMBOL) {}

    bool IsWalkable(Actor* actor) override { return true; }

protected:
    void OnStep(Game* game, Actor* actor) override
    {
        SetDiscovered(true);
        MessageBus::GetInstance()->Publish(new Log_Message("You step on a plain floor."));
    }
};

class WallTile : public Tile
{
public:
    WallTile() : Tile('#') {}
    bool IsWalkable(Actor* actor) override { return false; }

protected:
    void OnStep(Game* game, Actor* actor) override
    {
    }
};

class ExitTile : public Tile
{
public:
    ExitTile() : Tile('E') {}
    bool IsWalkable(Actor* actor) override { return true; }

protected:
    void OnStep(Game* game, Actor* actor) override;
};

class TrapTile : public Tile {
public:
    int myDamage;
    Actor* myTrapActor;

    TrapTile(Actor* trapActor) : Tile('^'), myDamage(10), myTrapActor(trapActor) {}

    bool IsWalkable(Actor* actor) override { return true; }

protected:
    void OnStep(Game* game, Actor* actor) override;
};