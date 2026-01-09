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
	const int BET_MULTI_HIGHER_OR_LOWER = 3;
	static const int DECK_SIZE = 13;
	const int DECK_SIZE_TO_INDEX_OFFSET = 1;
	const int REQUIRED_POINTS = 9;
	const int CURRENT_POINTS = 0;

	const int DEFAULT_CARDS_LEFT[DECK_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	struct Cards
	{
		const char* CARD_LABELS[DECK_SIZE] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
		const int CARD_VALUES[DECK_SIZE] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
		int cardsLeft[DECK_SIZE];
	};

	int myMoneyEarned;
	Cards myCards;
	HighOrLowPoints myPoints;
};
