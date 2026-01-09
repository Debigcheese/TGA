#pragma once
#include "Structs.h"

class HigherOrLower
{
public:
	HigherOrLower();
	int GetMoneyEarned() const;
	void SetMoneyEarned(int aNewMoney);

	void PlayHigherOrLower(Account& aAccount);
	//HigherOrLower
	int DrawRandomCard();
	bool CompareCards(int aPreviousCard, int aNewCard) const;
	bool IsHigherOrLowerGameOver() const;

private:
	const int myBetMulti = 3;
	static const int DECK_SIZE = 13;
	const int myDeckSizeOffset = 1;
	const int myRequiredPoints = 9;
	const int myCurrentPoints = 0;

	const int myDefaultCardsLeft[DECK_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	struct Cards
	{
		const char* myCardLabels[DECK_SIZE] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
		const int myCardValues[DECK_SIZE] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
		int cardsLeft[DECK_SIZE];
	};

	int myMoneyEarned;
	Cards myCards;
	HighOrLowPoints myPoints;
};
