#pragma once

class ITargetable
{
public:
    virtual ~ITargetable() {}
    virtual bool IsTargetable() const = 0;
};