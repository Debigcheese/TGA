#pragma once
class Entity;

class Component
{
public:
	virtual ~Component() = default;

	virtual void Update(float aDeltaTime);

	virtual void OnAdded();

	void SetOwner(Entity* aEntity) { myOwner = aEntity; }

protected:
	Entity* myOwner = nullptr;
};
