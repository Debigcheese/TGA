
#include <iostream>
#include <random>

enum class TableOption
{
	Menu = 0,
	GuessingGame = 1,
	OddOrEven = 2,
	SpinTheWheel = 3,
	Stats = 4,
	Quit = 5,
};

enum class GameAction
{
	Play = 1,
	ChangeBet = 2,
	ShowRules = 3,
	LeaveTable = 4,
};

struct Account
{
	int money;
	int bet;
};

struct Table
{
	TableOption currentTable;
	int statArr[5];
	int moneyArr[2];
};

int ReadIntInRange(int aMinValue, int aMaxValue);
int RollDice();
void ChangeBet(Account& account);
void UpdateStats(Table& table, bool isWin);

void EnterTable(Account& account, Table& table);
void EvaluateTableEarnings(Account& account, Table& table);
void HandleBankruptcy(Account& account, Table& table);

// Print to console
void ShowIntro(const Account& account);
void ShowPersonalDetails(const Account& account);
void ShowOptions(const Table& table);
void ShowRules(const Table& table);
void ShowStats(const Table& table);
//void ShowTableMessage();

// Games logic
void PlayGuessingRound(Account& account, Table& table);
void PlayOddEvenRound(Account& account, Table& table);
void PlaySpinWheelRound(Account& account, Table& table);

// Main
void MainMenu(Account& account, Table& table);

int ReadIntInRange(int aMinValue, int aMaxValue)
{
	int value;
	while (true)
	{
		std::cin >> value;
		if (value >= aMinValue && value <= aMaxValue)
		{
			return value;
		}
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Invalid. Enter a number between " << aMinValue << " and " << aMaxValue << ": ";
	}
}

int RollDice()
{
	std::random_device rd;
	std::mt19937 rng{ rd() };
	std::uniform_int_distribution<int> dist(1, 6);
	return dist(rng);
}

void ChangeBet(Account& account)
{
	std::cout << "Enter bet (1 - " << account.money << "): ";
	int newBet = ReadIntInRange(1, account.money);

	account.bet = newBet;
	if (account.bet == account.money)
	{
		std::cout << "\nAll in! The guards raise an eyebrow as you push everything in...\n";
		system("pause");
	}
}

void HandleBankruptcy(Account& account, Table& table)
{
	if (account.money <= 0)
	{
		std::cout << "\nYou're out of money! Security drag you out of the casino.\n";
		table.currentTable = TableOption::Quit;
	}
	if (account.money < account.bet && table.currentTable != TableOption::Quit)
	{
		std::cout << "\nYour bet is higher than what is currently in your wallet!, please change bet amount.\n";
		ChangeBet(account);
	}

}

void UpdateStats(Table& table, bool isWin)
{

	int arrIndex = 0;
	int statArrTemp[5] = {};

	for (int i = 0; i < 5; i++)
	{
		statArrTemp[i] = table.statArr[i]; //make a copy array
	}

	for (int i = 0; i < 4; i++)
	{
		if (table.statArr[0] == 0) // is index 0 empty?
		{
			break; //free spot
		}
		else
		{
			table.statArr[i + 1] = statArrTemp[i]; // move all indexes to the left [W][L][L][L][W] -> [0][W][L][L][L]
		}
	}

	arrIndex = 0;

	if (isWin)
	{
		table.statArr[arrIndex] = 1; // 1 = win
	}
	else
	{
		table.statArr[arrIndex] = -1; // -1 = loss
	}

	ShowStats(table);
}

// ---------- Print to console ----------
void ShowIntro(const Account& account)
{
	std::cout << "Welcome to the funky basement casino!\n";
	std::cout << "You start with $" << account.money << ".\n\n";
	system("pause");
	system("cls");
}

void ShowPersonalDetails(const Account& account)
{
	system("cls");
	std::cout << "Wallet: " << account.money << " kr. \nCurrent bet: " << account.bet << " kr.\n";
}

void ShowOptions(const Table& table)
{
	if (table.currentTable == TableOption::Menu)
	{
		std::cout
			<< "\n<--- Main Menu --->\n"
			<< "1) Guess The Sum\n"
			<< "2) Odd or Even\n"
			<< "3) Spin The Wheel\n"
			<< "4) Show Stats\n"
			<< "5) Leave casino\n"
			<< "Choice: ";
	}
	else if (table.currentTable == TableOption::GuessingGame)
	{
		std::cout
			<< "\n=== Table: Guess The Sum ===\n"
			<< "1) Play a round\n"
			<< "2) Change bet\n"
			<< "3) Show rules\n"
			<< "4) Leave table\n"
			<< "Choice: ";
	}
	else if (table.currentTable == TableOption::OddOrEven)
	{
		std::cout
			<< "\n=== Table: Odd or Even ===\n"
			<< "1) Play a round\n"
			<< "2) Change bet\n"
			<< "3) Show rules\n"
			<< "4) Leave table\n"
			<< "Choice: ";
	}
	else if (table.currentTable == TableOption::SpinTheWheel)
	{
		std::cout
			<< "\n=== Table: Spin The Wheel ===\n"
			<< "1) Play a round\n"
			<< "2) Change bet\n"
			<< "3) Show rules\n"
			<< "4) Leave table\n"
			<< "Choice: ";
	}

}

void ShowRules(const Table& table)
{
	if (table.currentTable == TableOption::GuessingGame)
	{
		std::cout
			<< "\n--- Rules: Guess The Sum ---\n"
			<< "Guess the sum of two dice (2-12).\n"
			<< "Two dice are rolled and shown, plus the total.\n"
			<< "Wrong guess: you lose your bet.\n"
			<< "Payout: 5x on correct guess.\n";
	}
	else if (table.currentTable == TableOption::OddOrEven)
	{
		std::cout
			<< "\n--- Rules: Odd or Even ---\n"
			<< "Pick Odd (1) or Even (2). Two dice are rolled and shown.\n"
			<< "Win if both dice are odd when you picked Odd, or both even when you picked Even.\n"
			<< "Mixed parity means the house wins. Sum does not matter.\n"
			<< "Payout: 2x on win, otherwise you lose your bet.\n";
	}
	else if (table.currentTable == TableOption::SpinTheWheel)
	{
		std::cout
			<< "\n--- Rules: Spin The Wheel ---\n"
			<< "The wheel shows 3 random symbols, chosen from 6 possible ones.\n"
			<< "Win a small prize if two symbols match and the third is different.\n"
			<< "Win a large prize if all three symbols match, JACKPOT!\n"
			<< "If all three symbols are different the house wins and you lose your bet.\n"
			<< "Payout: 2x for two of a kind, 40x for three of a kind.\n";
	}
	system("pause");
}

void ShowStats(const Table& table)
{
	std::cout << "\nYour five most recent games: \n";

	for (int i = 0; i < 5; i++)
	{
		std::cout << i + 1 << ": ";

		if (table.statArr[i] == -1)
		{
			std::cout << "Loss";
		}
		else if (table.statArr[i] == 1)
		{
			std::cout << "Win";
		}
		else
		{
			std::cout << "Empty";

		}
		std::cout << "\n";
	}
}

// Table
void EvaluateTableEarnings(Account& account, Table& table)
{
	int tableIndex = static_cast<int>(table.currentTable);

	int maxEarning = 400;
	int minEarning = -150;

	if (table.moneyArr[tableIndex - 1] == 0) // first time
	{
		std::cout << "\nThe dealer greets you with a sly smile.\n";

	}
	else if (table.moneyArr[tableIndex - 1] > maxEarning)
	{
		std::cout
			<< "\nYou've been on fire at this table, winning far too much...\n"
			<< "The pit boss whispers to the guards, and they politely escort you away.\n"
			<< "You are no longer welcome at this table.\n";
		system("pause");
		MainMenu(account, table);
	}
	else if (table.moneyArr[tableIndex - 1] < minEarning)
	{
		std::cout
			<< "\nThis table has not been kind to you...\n"
			<< "The dealer smirks as your losses keep piling up.\n"
			<< "Maybe it's time to try your luck somewhere else.\n";
	}
	else
	{
		std::cout
			<< "\nYour streak here has been mixed, some wins, some losses.\n"
			<< "The dealer greets you with a sly smile.\n";
	}
	system("pause");
}

void EnterTable(Account& account, Table& table)
{
	EvaluateTableEarnings(account, table);

	TableOption chosenTable = table.currentTable;
	while (table.currentTable == chosenTable)
	{
		ShowPersonalDetails(account);
		ShowOptions(table);
		HandleBankruptcy(account, table);

		GameAction action = static_cast<GameAction>(ReadIntInRange(1, 4));

		switch (action)
		{
		case GameAction::Play:
		{
			switch (table.currentTable)
			{
			case TableOption::GuessingGame:
			{
				PlayGuessingRound(account, table);
				break;
			}
			case TableOption::OddOrEven:
			{
				PlayOddEvenRound(account, table);
				break;
			}
			case TableOption::SpinTheWheel:
			{
				PlaySpinWheelRound(account, table);
				break;
			}
			default: break;
			}
			HandleBankruptcy(account, table);
			break;
		}
		case GameAction::ChangeBet:
		{
			ChangeBet(account);
			break;
		}
		case GameAction::ShowRules:
		{
			ShowRules(table);
			break;
		}
		case GameAction::LeaveTable:
		{
			table.currentTable = TableOption::Menu;
			break;
		}
		default: break;
		}
	}
}

// ---------- Guessing Game ----------
void PlayGuessingRound(Account& account, Table& table)
{
	std::cout << "\nEnter your guess (2-12): ";
	int guess = ReadIntInRange(2, 12);

	int diceOne = RollDice();
	int diceTwo = RollDice();
	int sum = diceOne + diceTwo;

	std::cout << "\nDice 1: " << diceOne << ", Dice 2: " << diceTwo << "  -> Sum: " << sum << "\n";

	if (guess == sum)
	{
		int win = account.bet * 5;
		account.money += win;
		table.moneyArr[0] += win;
		std::cout << "BINGO! Your payout: " << win << " kr.\n";
		UpdateStats(table, true);
	}
	else
	{
		account.money -= account.bet;
		table.moneyArr[0] -= account.bet;
		std::cout << "Miss! You lose " << account.bet << " kr.\n";
		UpdateStats(table, false);
	}
	system("pause");
}

// ---------- Odd or Even ----------
void PlayOddEvenRound(Account& account, Table& table)
{
	std::cout << "\nChoose: Odd (1) or Even (2): ";
	int pick = ReadIntInRange(1, 2);

	int dice1 = RollDice();
	int dice2 = RollDice();
	std::cout << "Dice 1: " << dice1 << ", Dice 2: " << dice2 << "\n";

	bool dice1Odd = (dice1 % 2 == 1);
	bool dice2Odd = (dice2 % 2 == 1);

	bool bothOdd = dice1Odd && dice2Odd;
	bool bothEven = !dice1Odd && !dice2Odd;

	bool pickedOdd = (pick == 1);
	bool playerWins = (pickedOdd && bothOdd) || (!pickedOdd && bothEven);

	if (playerWins)
	{
		int win = account.bet * 2;
		account.money += win;
		table.moneyArr[1] += win;
		std::cout << "You win! Your payout: " << win << " kr.\n";
		UpdateStats(table, true);
	}
	else
	{
		account.money -= account.bet;
		table.moneyArr[1] -= account.bet;
		std::cout << "House wins. You lose " << account.bet << " kr.\n";
		UpdateStats(table, false);
	}
	system("pause");
}

// ---------- Spin the wheel ----------
void PlaySpinWheelRound(Account& account, Table& table)
{
	std::cout << "\nSpin The Wheel (1):  ";
	ReadIntInRange(1, 1);

	int dice1 = RollDice();
	int dice2 = RollDice();
	int dice3 = RollDice();

	std::cout << dice1 << " | " << dice2 << " | " << dice3 << "\n";

	int win = account.bet;

	if (dice1 == dice2 && dice2 == dice3)
	{

		win *= 40;
		account.money += win;
		table.moneyArr[2] += win;
		std::cout << "<--- 40X WIN! --->\n";
		std::cout << "Your payout: " << win << " kr.\n";
		UpdateStats(table, true);

	}
	else if ((dice1 == dice2) || (dice2 == dice3) || (dice3 == dice1))
	{

		win *= 2;
		account.money += win;
		table.moneyArr[2] += win;
		std::cout << "<--- 2X WIN! --->\n";
		std::cout << "Your payout: " << win << " kr.\n";
		UpdateStats(table, true);
	}
	else
	{
		account.money -= account.bet;
		table.moneyArr[2] -= account.bet;
		std::cout << "House wins. You lose " << account.bet << " kr.\n";
		UpdateStats(table, false);
	}
	system("pause");
}

// ---------- Main ----------
void MainMenu(Account& account, Table& table)
{
	table.currentTable = TableOption::Menu;

	while (table.currentTable == TableOption::Menu)
	{

		ShowPersonalDetails(account);
		ShowOptions(table);
		HandleBankruptcy(account, table);

		TableOption chosenTable = static_cast<TableOption>(ReadIntInRange(1, 5));

		switch (chosenTable)
		{
		case TableOption::GuessingGame:
		{
			table.currentTable = TableOption::GuessingGame;
			//EnterTable(account, table);
			break;
		}
		case TableOption::OddOrEven:
		{
			table.currentTable = TableOption::OddOrEven;
			//EnterTable(account, table);
			break;
		}
		case TableOption::SpinTheWheel:
		{
			table.currentTable = TableOption::SpinTheWheel;
			//EnterTable(account, table);
			break;
		}
		case TableOption::Stats:
		{
			ShowStats(table);
			system("pause");
			break;
		}
		case TableOption::Quit:
		{
			std::cout << "\nYou leave with " << account.money << " kr. Come back soon!\n";
			table.currentTable = TableOption::Quit;
			break;
		}
		default: break;
		}

		EnterTable(account, table);
	}
}

int main()
{
	const int DEFAULT_MONEY = 1000;
	const int DEFAULT_BET = 10;
	const TableOption DEFAULT_TABLEOPTION = TableOption::Menu;

	Account account; //= { DEFAULT_MONEY, DEFAULT_BET };
	account.money = DEFAULT_MONEY;
	account.bet = DEFAULT_BET;

	Table table;
	table.currentTable = DEFAULT_TABLEOPTION;
	table.statArr; //stats
	//[0] = guessing game | [1] = OddorEven | [2] = SpinTheWheel
	table.moneyArr;//money per table

	ShowIntro(account);
	MainMenu(account, table);
	return 0;
}
