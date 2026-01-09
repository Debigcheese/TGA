#pragma once
#include <functional>
#include "Component.h"

class Bomb : public Component
{
	using ExplodeCallback = std::function<void()>;

public:
	Bomb() = default;
	~Bomb() override;
	void OnAdded() override;

	void Update(float aTimeDelta) override;
	void SetOnExplode(ExplodeCallback aCallback) { myOnExplode = aCallback; }

private:
	ExplodeCallback myOnExplode;
};
