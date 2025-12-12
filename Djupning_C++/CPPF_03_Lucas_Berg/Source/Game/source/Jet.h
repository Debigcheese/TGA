#pragma once
#include "Enemy.h"

class Jet : public Enemy
{
	using DropBombCallback = std::function<void(const Tga::Vector2f& aPosition)>;

public:
	Jet();
	~Jet() override;

	void Update(float aTimeDelta) override;

	void SetOnDropBomb(DropBombCallback aCallback) { myOnDropBomb = aCallback; }

	bool GetDropBomb() const { return myDropBomb; }
	void SetBombDropped() { myJetBombDropped = true; }

private:
	DropBombCallback myOnDropBomb;

	bool myDropBomb = false;

	bool myJetBombDropped = false;
};
