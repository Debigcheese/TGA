#include "Spell.h"

#include "DamagePacket.h"
#include "ITargetable.h"
#include "LogMessage.h"
#include "StatsComponent.h"
#include "Actor.h"
#include "Game.h"

bool Fireball::Cast(Game* game, Actor* caster, int targetX, int targetY)
{
    ITargetable* rawTarget = game->GetActorAt(targetX, targetY);
    if (!rawTarget || !rawTarget->IsTargetable())
    {
        MessageBus::GetInstance()->Publish(new Log_Message("The fireball fizzles into thin air."));
        return true;
    }

    Actor* target = dynamic_cast<Actor*>(rawTarget);
    if (target)
    {
        StatsComponent* targetStats = target->GetComponent<StatsComponent>();
        if (targetStats)
        {
            DamagePacket dmg;
            dmg.amount = 30;
            dmg.myType = game->m_fireType;
            dmg.mySource = caster;
            targetStats->HandleDamage(dmg);
            return true;
        }
    }
    MessageBus::GetInstance()->Publish(new Log_Message("The fireball fizzles."));
    return true;
}

bool Heal::Cast(Game* game, Actor* caster, int targetX, int targetY)
{
    ITargetable* rawTarget = game->GetActorAt(targetX, targetY);
    Actor* target = dynamic_cast<Actor*>(rawTarget);

    if (!target || !target->myIsActive)
    {
        target = caster;
    }

    StatsComponent* casterStats = target->GetComponent<StatsComponent>();
    if (casterStats)
    {
        casterStats->setHp(casterStats->getHp() + 40);
        if (casterStats->getHp() > casterStats->getMaxHp())
        {
            casterStats->setHp(casterStats->getMaxHp());
        }
        MessageBus::GetInstance()->Publish(new Log_Message(target->myName + " feels a warm energy."));
        return true;
    }
    return false;
}

