#pragma once

class DamageTypeEffect;
class Actor;

struct DamagePacket
{
    int amount;
    DamageTypeEffect* myType;
    Actor* mySource;
};