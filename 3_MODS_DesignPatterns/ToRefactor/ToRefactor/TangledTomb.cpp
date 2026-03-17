#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <conio.h>

#include "Actor.h"
#include "ITargetable.h"
#include "Component.h"
#include "IMapGenerationStrategy.h"
#include "IMapPass.h"
#include "IMessageListener.h"
#include "Tile.h"
#include "MessageBus.h"
#include "MapConfigSingleton.h"
#include "LogMessage.h"
#include "ActorDiedMessage.h"
#include "DamagePacket.h"
#include "DamageTypeEffect.h"
#include "Spell.h"
#include "StatsComponent.h"
#include "Game.h"
#include "GameState.h"

class Game;
class Actor;
class StatsComponent;
class GameState;
class Tile;
class MessageState;
class TargetState;

// ----------------------------------------------------
// MAINdd
// ----------------------------------------------------

int main()
{
    MapConfigSingleton::GetInstance();
    Game myGame;
    myGame.Run();
    return 0;
}