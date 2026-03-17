#include "Tile.h"

#include "StatsComponent.h"
#include "Actor.h"
#include "Game.h"
#include "DamagePacket.h"


void TrapTile::OnStep(Game* game, Actor* actor)
{
    Tile::OnStep(game, actor);
    MessageBus::GetInstance()->Publish(new Log_Message("You've stepped on a trap!"));

    if (myTrapActor) {
        StatsComponent* trapStats = myTrapActor->GetComponent<StatsComponent>();
        if (trapStats) {
            DamagePacket dmg;
            dmg.amount = myDamage;
            dmg.myType = game->m_physicalType;
            dmg.mySource = myTrapActor;

            StatsComponent* targetStats = actor->GetComponent<StatsComponent>();
            if (targetStats) {
                targetStats->HandleDamage(dmg);
            }
        }
    }
}

void ExitTile::OnStep(Game* game, Actor* actor)
{

    if (actor == game->myPlayer)
    {
        MessageBus::GetInstance()->Publish(new Log_Message("You found the exit!"));
        game->ChangeGameState(NULL);
    }
}