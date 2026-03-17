#pragma once
#include "Component.h"
#include "MessageBus.h"
#include "IMessageListener.h"

struct DamagePacket;

class StatsComponent : public Component, public IMessageListener
{
private:
    int myHp;
    int myMaxHp;
    int myAttack;
    int myDefense;
    int myMana;
    int myMaxMana;
public:
    int myXP;
    int myLevel;

    StatsComponent(int hp, int atk, int def, int mana = 0)
        : myHp(hp), myMaxHp(hp), myAttack(atk), myDefense(def),
        myMana(mana), myMaxMana(mana), myXP(0), myLevel(1)
    {
        MessageBus::GetInstance()->Subscribe(this);
    }

    int getHp() const { return myHp; }
    int getMaxHp() const { return myMaxHp; }
    int getAttack() const { return myAttack; }
    int getDefense() const { return myDefense; }
    int getMana() const { return myMana; }
    int getMaxMana() const { return myMaxMana; }

    void setHp(int newHp) { myHp = newHp; }
    void setMana(int newMp) { myMana = newMp; }

    virtual bool HandleDamage(DamagePacket& dmg);
    void HandleMessage(Message* msg) override;
};

class FireImpStatsComponent : public StatsComponent
{
public:
    FireImpStatsComponent(int hp, int atk, int def) : StatsComponent(hp, atk, def) {}
    bool HandleDamage(DamagePacket& dmg) override;
};