#pragma once
#include "GameStructs.h"
#include "SpellType.h"

class Player;

class Spell
{
public:
    Spell(SpellType* aSpellType, int aId);

    void UpdateOnHitCount();
    void ActivateSpell();

    SpellAttributes GetSpellAttributes() const { return mySpellType->GetSpellAttributes(); }
    Attributes GetAttributes() const { return GetSpellAttributes().attributes; }
    const SpellState& GetState() const { return myState; }
    bool GetSpellFinished() const;
    int GetId() const { return myId; }
    int GetHitCount() const;

private:
    //CONSTANTS
    static constexpr int DEFAULT_HIT_COUNT = 10;
    int myId;
    SpellState myState;
    SpellType* mySpellType;
};
