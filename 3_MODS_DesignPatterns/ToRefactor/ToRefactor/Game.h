#pragma once
#include <vector>

#include "Coordinate.h"
#include "DamageTypeEffect.h"
#include "IMapGenerationStrategy.h"
#include "Tile.h"

class GameState;

class Game
{
public:
    int myMapWidth;
    int myMapHeight;

    char m_lastPlayerInput;

    std::vector<std::vector<Tile*>> myMap;
    std::vector<Actor*> m_actorList;
    Actor* myPlayer;

    GameState* myCurrentState;

    std::vector<std::string> LogEntry;

    PhysicalDamage* m_physicalType;
    FireDamage* m_fireType;
    IceDamage* m_iceType;
    IMapGenerationStrategy* myMapGenStrategy;

    Game();
    ~Game();

    // Core Methods
    void Run();
    void ChangeGameState(GameState* newState);
    void updateLog(std::string message);

    // Game Logic Helpers
    Actor* GetActorAt(int x, int y);
    void CheckPlayerVisibility(int maxDist);
    Coordinate FindRandomOpenTile();

    // Guaranteed Connectivity Check (still needed)
    void EnsureExitReachable();

    // Procedural Map Generation Helpers (public for passes/strategies to call)
    void InitializeMap();
    // This function uses the strange 'Coordinate' struct defined globally above.
    void CarveRandomPath(Coordinate start, int steps, int areaSize);
};
