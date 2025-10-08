// UnitTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "utilityFunctions.h"
#include <iostream>

using namespace CommonUtilies;

int main()
{
	std::cout << "--- Testing Max ---\n";
	std::cout << "Max(5, 3) = " << Max(5, 3) << " (first is largest)\n";
	std::cout << "Max(2, 7) = " << Max(2, 7) << " (second is largest)\n";
	std::cout << "Max(-4, 2) = " << Max(-4, 2) << " (second positive)\n";
	std::cout << "Max(4, -2) = " << Max(4, -2) << " (first positive)\n";
	std::cout << "Max(-5, -3) = " << Max(-5, -3) << " (both negative, second largest)\n";
	std::cout << "Max(-2, -6) = " << Max(-2, -6) << " (both negative, first largest)\n\n";

	std::cout << "--- Testing Min ---\n";
	std::cout << "Min(5, 3) = " << Min(5, 3) << " (second is smallest)\n";
	std::cout << "Min(2, 7) = " << Min(2, 7) << " (first is smallest)\n";
	std::cout << "Min(-4, 2) = " << Min(-4, 2) << " (first negative smallest)\n";
	std::cout << "Min(4, -2) = " << Min(4, -2) << " (second negative smallest)\n";
	std::cout << "Min(-5, -3) = " << Min(-5, -3) << " (both negative, first smallest)\n";
	std::cout << "Min(-2, -6) = " << Min(-2, -6) << " (both negative, second smallest)\n\n";

	std::cout << "--- Testing Clamp ---\n";
	std::cout << "Clamp(5, 0, 10) = " << Clamp(5, 0, 10) << " (inside range)\n";
	std::cout << "Clamp(10, 0, 10) = " << Clamp(10, 0, 10) << " (exact max)\n";
	std::cout << "Clamp(0, 0, 10) = " << Clamp(0, 0, 10) << " (exact min)\n";
	std::cout << "Clamp(15, 0, 10) = " << Clamp(15, 0, 10) << " (above max)\n";
	std::cout << "Clamp(-3, 0, 10) = " << Clamp(-3, 0, 10) << " (below min)\n";
	std::cout << "Clamp(-5, -10, -1) = " << Clamp(-5, -10, -1) << " (negative range)\n";
	std::cout << "Clamp(3, -5, 5) = " << Clamp(3, -5, 5) << " (mixed range)\n";
	std::cout << "Clamp(7, 7, 7) = " << Clamp(7, 7, 7) << " (min=max)\n";
	// The following line will assert if uncommented:
	// std::cout << "Clamp(5, 10, 0) = " << Clamp(5, 10, 0) << "\n\n";

	std::cout << "\n--- Testing Abs ---\n";
	std::cout << "Abs(-8) = " << Abs(-8) << "\n";
	std::cout << "Abs(12) = " << Abs(12) << "\n";

	std::cout << "\n--- Testing Swap ---\n";
	int a = 5, b = 10;
	std::cout << "Before Swap: a=" << a << ", b=" << b << "\n";
	Swap(a, b);
	std::cout << "After Swap: a=" << a << ", b=" << b << "\n";

	int c = -4, d = -9;
	std::cout << "Before Swap: c=" << c << ", d=" << d << "\n";
	Swap(c, d);
	std::cout << "After Swap: c=" << c << ", d=" << d << "\n";

	int same = 42;
	std::cout << "Before Swap(same): " << same << "\n";
	Swap(same, same);
	std::cout << "After Swap(same): " << same << "\n";

	std::cout << "\n--- Testing Lerp ---\n";
	std::cout << "Lerp(0, 10, 0) = " << Lerp(0.0f, 10.0f, 0.0f) << " (should be 0)\n";
	std::cout << "Lerp(0, 10, 1) = " << Lerp(0.0f, 10.0f, 1.0f) << " (should be 10)\n";
	std::cout << "Lerp(0, 10, 0.5) = " << Lerp(0.0f, 10.0f, 0.5f) << " (should be 5)\n";

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
