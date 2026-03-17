#pragma once
#include <string>


class DamageTypeEffect
{
public:
    virtual ~DamageTypeEffect() {}
    virtual std::string GetName() const = 0;
};

class PhysicalDamage : public DamageTypeEffect
{
public:
    std::string GetName() const override { return "PHYSICAL"; }
};

class FireDamage : public DamageTypeEffect
{
public:
    std::string GetName() const override { return "FIRE"; }
};

class IceDamage : public DamageTypeEffect
{
public:
    std::string GetName() const override { return "ICE"; }
};