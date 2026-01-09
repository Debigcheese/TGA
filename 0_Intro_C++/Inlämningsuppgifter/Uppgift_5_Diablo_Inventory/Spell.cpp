#include "Spell.h"
#include "Utils.h"

using namespace Utils;

Spell::Spell(SpellType* aSpellType, int aId)
    : myId(aId),
      myState{false, DEFAULT_HIT_COUNT},
      mySpellType(aSpellType)
{
}

void Spell::UpdateOnHitCount()
{
    if (myState.isActive)
    {
        myState.hitCount--;
    }
}

void Spell::ActivateSpell()
{
    myState.isActive = true;
}

bool Spell::GetSpellFinished() const
{
    if (myState.hitCount < 0)
    {
        return true;
    }
    return false;
}

int Spell::GetHitCount() const
{
    return myState.hitCount;
}
