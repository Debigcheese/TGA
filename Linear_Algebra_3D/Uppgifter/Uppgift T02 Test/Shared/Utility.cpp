#include "stdafx.h"
#include "Shared/Utility.h"
#include <random>

namespace TestUtility
{
	std::mt19937 rEngine(6);

	float GetRandomFloat(float aMin, float aMax)
	{
		std::uniform_real_distribution<float> rnd(aMin, aMax);
		return rnd(rEngine);
	}

	double GetRandomDouble(double aMin, double aMax)
	{
		std::uniform_real_distribution<double> rnd(aMin, aMax);
		return rnd(rEngine);
	}

	int GetRandomInt(int aMin, int aMax)
	{
		std::uniform_int_distribution<int> rnd(aMin, aMax);
		return rnd(rEngine);
	}
}
