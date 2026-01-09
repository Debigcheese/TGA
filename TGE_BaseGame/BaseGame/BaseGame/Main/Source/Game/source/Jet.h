#pragma once
#include <functional>
#include "Component.h"
#include "tge/math/Vector2.h"

class Jet : public Component
{
	using DropBombCallback = std::function<void(const Tga::Vector2f& aPosition)>;

public:
	Jet() = default;
	~Jet() override;

	void Update(float aTimeDelta) override;
	void OnAdded() override;

	void SetOnDropBomb(DropBombCallback aCallback) { myOnDropBomb = aCallback; }

	bool GetDropBomb() const { return myDropBomb; }
	void SetBombDropped() { myJetBombDropped = true; }

private:
	DropBombCallback myOnDropBomb;

	bool myDropBomb = false;

	bool myJetBombDropped = false;

	bool myLeftSide = false;
};
