#pragma once

enum class Direction
{
    None = 0,
    West = 1,
    North = 2,
    East = 3,
    South = 4,
};

enum class Choice
{
    None = 0,
    Yes = 1,
    No = 2
};

enum class Action
{
    Combat = 1,
    Navigation = 2,
    LookAround = 3,
    Inventory = 4,
    Attributes = 5,
    Cheats = 6,
    Quit = 7,
};

enum class ItemAction
{
    Equip = 1,
    Drop = 2,
    Count,
};

enum class AttackType
{
    None = 0,
    QuickAttack = 1,
    HeavyAttack = 2,
    SlashAttack = 3,
    AttackInfo = 4,
};

enum class AttriMenu
{
    Attributes = 1,
    DerivedAttributes = 2,
    Return = 3,
};

enum class Scavenge
{
    Floor = 1,
    Chests = 2,
    Spells = 3,
    Return = 4,
};

enum class LockType
{
    None = 0,
    Agility = 1,
    Strength = 2,
    Unlocked = 3,
};

enum class EnemyNames
{
    None = 0,
    Bat = 1,
    Skeleton = 2,
    Undead = 3,
    Beast = 4,
    Humanoid = 5,
    Elemental = 6,
    Demon = 7,
};

enum class CheatType
{
    None = 4,
    Invincible = 1,
    OneShot = 2,
    Ghost = 3,
};

enum class AttributeType
{
    None = 0,
    Strength = 1,
    //styrka (10-99)
    Agility = 2,
    // smidighet (10-99)
    Endurance = 3,
    // fysik (10-99)
    MaxHealth = 4,
    CurrentHealth = 5,
    CarryCapacity = 6,
    Damage = 7,
    Defense = 8,
};

enum class EquipmentType
{
    None = 0,
    Head = 1,
    Hand = 2,
    Body = 3,
    Legs = 4,
    Feet = 5,
    Amulet = 6,
    Count
};

enum class Rarity
{
    None = 0,
    Bronze = 1,
    Silver = 2,
    Gold = 3,
    Legendary = 4,
};

enum class TextColor
{
    Red,
    Brown,
    Silver,
    Gold,
    Magenta
};

enum class ItemKey
{
    None = 0,
    Eclipse,
    GodSword,
    Aegis,
    Backpack,
    StormBreaker,
    DragonScale,
    KnightHelm,
    BloodFang,
    CelestialShield,
    WarAxe,
    LeatherBoots,
    VoidReaver,
    IronChestplate,
    TrainingSword,
    SwiftGreaves,
    TitanGauntlets,
    CrusaderPlate,
    ShadowstepBoots,
    BerserkerAmulet,
    QuartzAmulet,
    Sunpiercer,
    ThunderMaul,
    OakheartChest,
    SteelKneeguards,
    FalconAmulet,
    VanguardHelm,
    ForgemasterGloves,

    Count
};

enum class SpellKey
{
    None = 0,
    MagicMissile,
    Fireball,
    MeteorStrike,
    ChainLightning,
    AcidSpray,
    Earthquake,
    StoneSkin,
    Shockwave,
    PhoenixFlame,
    WindSlash,
    Hurricane,
    HealingLight,
    DivineShield,
    ArcaneBlast,
    BlackHole,
    Count
};

enum class EnemyKey
{
    None = 0,
    Bat = 1,
    Skeleton = 2,
    Undead = 3,
    Beast = 4,
    Humanoid = 5,
    Elemental = 6,
    Demon = 7,
    Count
};
