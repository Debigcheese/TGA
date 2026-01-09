#pragma once
#include <functional>

#include "Component.h"
#include "HealthComponent.h"
#include "MovementComponent.h"
#include "Paratrooper.h"

class ParachuteComponent : public Component
{
public:
	ParachuteComponent();
	~ParachuteComponent() override = default;

	void OnAdded() override;
	void Update(float aDeltaTime) override;
	void SetOnDestroyParachute(std::function<void(Entity*)> aCallback) { myDestroyParachuteCallback = aCallback; }

	void SetParachuteTrooper(Entity* aParatrooper);
	Entity* GetParachuteTrooper() const { return myEntityTrooper; }
	void OnTrooperDestroy() { myEntityTrooper = nullptr; }

private:
	std::function<void(Entity*)> myDestroyParachuteCallback;
	std::shared_ptr<HealthComponent> myHealthComponent;

	bool myDestroyed = false;
	Entity* myEntityTrooper;
};
