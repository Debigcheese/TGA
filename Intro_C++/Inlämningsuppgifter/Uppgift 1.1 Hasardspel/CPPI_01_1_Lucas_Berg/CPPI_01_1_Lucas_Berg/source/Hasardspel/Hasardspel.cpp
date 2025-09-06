// Hasardspel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <random>
#include <iostream>
#include <windows.h>

void PlayCasino();
void RollDice();
void ShowInstructions();
bool PlayAgain();

bool showInstructions = true;

void RollDice() {

	system("cls");

	//timer to roll dice
	for (volatile long long i = 0; i < 500; i++) {

		std::cout << "\033[3mRolling dice\033[0m";

		if (i <= 100) {
			std::cout << "\033[3m.\033[0m \n";
			system("cls");
		}
		else if (i <= 200) {
			std::cout << "\033[3m..\033[0m \n";
			system("cls");
		}
		else if (i <= 300) {
			std::cout << "\033[3m...\033[0m \n";
			system("cls");
		}
		else if (i <= 400) {
			std::cout << "\033[3m.\033[0m \n";
			system("cls");
		}
		else {
			std::cout << "\033[3m..\033[0m \n";
			system("cls");
		}

	}
}

void ShowInstructions() {

	if (showInstructions) {
		std::cout << "Welcome to the casino!\n";
		std::cout << "Guess a number between 2-12\n";
		showInstructions = false;
	}
}

bool PlayAgain() {

	std::cout << "\nPress 1 to play again \npress 2 to quit" << std::endl;

	while (true) {

		int playAgain;
		std::cin >> playAgain;

		if (std::cin.fail() || playAgain < 1 || playAgain > 2) {

			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Invalid choice \nPress 1 to play again \npress 2 to quit" << std::endl;

			continue;
		}
		if (playAgain == 2) {
			return false;
		}
		if (playAgain == 1) {
			system("cls");
			PlayCasino();
			return true;

		}
	}
}

void PlayCasino() {

	if (showInstructions) {
		ShowInstructions();
	}
	else {
		system("cls");
		std::cout << "Guess a number\n";
	}

	while (true) {

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(1, 6);

		int guess;
		std::cin >> guess;
		std::cout << " guess:";

		int diceOne = dist(gen);
		int diceTwo = dist(gen);
		int sum = diceOne + diceTwo;

		if (std::cin.fail() || guess < 2 || guess > 12) {

			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Guess invalid, please guess a number between 2-12\n";

			continue;
		}

		//timer to roll dice
		RollDice();
		std::cout << "First dice: " << diceOne << "\tSecond dice: " << diceTwo << "\nYour guess: " << guess << "\nSum: " << sum << "\n";

		if (guess == sum) {
			std::cout << "Your guess was correct! \n" << std::endl;
		}
		else {
			std::cout << "Your guess was incorrect! \n" << std::endl;
		}
		break;
	}

}

int main()
{
	bool again = true;

	while (again) {
		PlayCasino();
		again = PlayAgain();
	}


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
