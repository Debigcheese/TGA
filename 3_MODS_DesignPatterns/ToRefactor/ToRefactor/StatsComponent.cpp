#include "StatsComponent.h"

#include "ActorDiedMessage.h"
#include "DamageTypeEffect.h"
#include "LogMessage.h"
#include "DamagePacket.h"
#include "Actor.h"

bool StatsComponent::HandleDamage(DamagePacket& dmg)
{
    int finalDamage = dmg.amount - myDefense;
    if (finalDamage < 1) finalDamage = 1;

    myHp -= finalDamage;
    std::string log = myOwner->myName + " takes " + std::to_string(finalDamage) + " damage.";
    MessageBus::GetInstance()->Publish(new Log_Message(log));

    if (myHp <= 0)
    {
        myOwner->myIsActive = false;
        MessageBus::GetInstance()->Publish(new ActorDiedMessage(myOwner, dmg.mySource));
    }
    return true;
}

void StatsComponent::HandleMessage(Message* msg)
{
    ActorDiedMessage* deathMsg = dynamic_cast<ActorDiedMessage*>(msg);
    if (deathMsg && deathMsg->myKiller == myOwner)
    {
        StatsComponent* victimStats = deathMsg->myVictim->GetComponent<StatsComponent>();
        if (victimStats)
        {
            int xpGain = victimStats->getMaxHp() / 2;

            myXP += xpGain;
            MessageBus::GetInstance()->Publish(new Log_Message("You gain " + std::to_string(xpGain) + " XP."));

            if (myXP >= (myLevel * 100))
            {
                myLevel++;
                myXP = 0;
                myAttack += 2;
                myMaxHp += 10;
                myHp = myMaxHp;
                MessageBus::GetInstance()->Publish(new Log_Message("You are now level " + std::to_string(myLevel) + "!"));
            }
        }
    }
}

bool FireImpStatsComponent::HandleDamage(DamagePacket& dmg)
{
    if (dynamic_cast<FireDamage*>(dmg.myType))
    {
        std::string log = "The " + myOwner->myName + " sizzles but takes no damage!";
        MessageBus::GetInstance()->Publish(new Log_Message(log));
        return false;
    }
    return StatsComponent::HandleDamage(dmg);
}