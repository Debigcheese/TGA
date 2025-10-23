#pragma once
#include "GameStructs.h"
#include "Player.h"

class Player;
class Room;

class CombatController
{
public:
    static constexpr int PLAYER_ATTACK_INDEX_INVALID = -1;
    static constexpr int PLAYER_ATTACK_INDEX_ZERO = 0;

    static constexpr int PLAYER_TARGET_ENEMY_MIN = 1;
    static constexpr int PLAYER_TARGET_INDEX_OFFSET = 1;

    // Damage and scaling params.
    static constexpr float DAMAGE_ZERO = 0.0f;
    static constexpr float HEAVY_MULTI_MIN = 0.75f;
    static constexpr float HEAVY_MULTI_MAX = 1.50f;
    static constexpr float SLASH_DMG_MULTI = 2.50f;
    static constexpr float DEFENSE_BASE_MULTI = 0.0f;
    static constexpr float DEFENSE_SCALING_FACTOR = 200.0f;

    CombatController(Player& aPlayer);
    void UpdateCombat(Room* aCurrentRoom);

    void ChooseTarget();
    void ChooseAttack();
    void Attack() const;

    const AttackData& GetAttackData() const { return myAttackData; }
    void SetAttackData(const AttackData& aData) { myAttackData = aData; }

    // ---- Calculations & checks ----
    float GetDamageFromAttackType() const;
    const AmountRange& GetHeavyDamageRange() const;
    float GetSlashDamage() const { return myPlayer.GetAttributes().damage / SLASH_DMG_MULTI; }
    float GetDefenseMultiplier() const;
    bool IsInvalidAttackIndex() const;

private:
    Player& myPlayer;
    Room* myCurrentRoom;
    AttackData myAttackData;
};
