#pragma once
#include <cassert>

namespace CommonUtilities
{
	template <typename T>
	constexpr T Max(const T& a, const T& b)
	{
		return (a > b) ? a : b;
	}


	template <typename T>
	constexpr T Min(const T& a, const T& b)
	{
		return (a < b) ? a : b;
	}

	template <typename T>
	constexpr T Clamp(const T& value, const T& min, const T& max)
	{
		assert(min <= max && "Clamp error: min cannot be greater than max!");
		return (value < min) ? min : (value > max) ? max : value;
	}


	template <typename T>
	constexpr T Abs(const T& value)
	{
		return (value < 0) ? -value : value;
	}

	template <typename T>
	constexpr T Lerp(const T& from, const T& to, const T& percentage)
	{
		return (from + percentage * (to - from));
	}

	template <typename T>
	constexpr void Swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}
}
