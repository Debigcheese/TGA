
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

const int INITIAL_MONEY = 1000;
const int DEFAULT_BET = 10;
const TableOption DEFAULT_TABLEOPTION = TableOption::Menu;

std::random_device g_rd;
std::mt19937 g_rng{ g_rd() };

int globalMoney = INITIAL_MONEY;
int globalBet = DEFAULT_BET;
TableOption globalCurrentTable;

int globalStatArr[5] = { 0 };
//[0] = guessing game | [1] = OddorEven | [2] = SpinTheWheel
int globalMoneyArr[2] = { 0 };

int ReadIntInRange(int aMinValue, int aMaxValue);
int RollDice();
void ChangeBet();
void UpdateStats(bool isWin);

void EnterTable(TableOption tableToEnter);
void EvaluateTableEarnings();
void HandleBankruptcy();

// Print to console
void ShowIntro();
void ShowPersonalDetails();
void ShowOptions();
void ShowRules();
void ShowStats();
//void ShowTableMessage();

// Games
void PlayGuessingRound();
void PlayOddEvenRound();
void PlaySpinWheelRound();

// Main
void MainMenu();


int ReadIntInRange(int aMinValue, int aMaxValue)
{
    int value;
    while (true)
    {
        if (globalMoney <= 0) 
        {
            HandleBankruptcy();
        }
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
    std::uniform_int_distribution<int> dist(1, 6);
    return dist(g_rng);
}

void ChangeBet()
{
    std::cout << "Enter bet (1 - " << globalMoney << "): ";
    int newBet = ReadIntInRange(1, globalMoney);

    globalBet = newBet;
    if (globalBet == globalMoney)
    {
        std::cout << "\nAll in! The guards raise an eyebrow as you push everything in...\n";
        system("pause");
    }
}

void HandleBankruptcy()
{
    if (globalMoney < globalBet) {
        std::cout << "\nYour bet is higher than what is currently in your wallet!, please change bet amount.\n";
        ChangeBet();
    }
    if (globalMoney <= 0)
    {
        std::cout << "\nYou're out of money! Security drag you out of the casino.\n";
        globalCurrentTable = TableOption::Quit;
    }
}

void UpdateStats(bool isWin) {

    int arrIndex = 0;
    int statArrTemp[5] = {};

    for (int i = 0; i < 5; i++)
    {
        statArrTemp[i] = globalStatArr[i]; //make a copy array
    }

    for (int i = 0; i < 4; i++) 
    {
        if (globalStatArr[0] == 0) // is index 0 empty?
        {
            break; //free spot
        }
        else 
        {
            globalStatArr[i+1] = statArrTemp[i]; // move all indexes to the left [W][L][L][L][W] -> [0][W][L][L][L]
        }
    }

    arrIndex = 0;

    if (isWin) 
    {
        globalStatArr[arrIndex] = 1; // 1 = win
    } 
    else 
    {
        globalStatArr[arrIndex] = -1; // -1 = loss
    }

    ShowStats();
}

// ---------- Print to console ----------
void ShowIntro()
{
    std::cout << "Welcome to the funky basement casino!\n";
    std::cout << "You start with $" << globalMoney << ".\n\n";
    system("pause");
    system("cls");
}

void ShowPersonalDetails() {
    system("cls");
    std::cout << "Wallet: " << globalMoney << " kr. \nCurrent bet: " << globalBet << " kr.\n";
}

void ShowOptions() {

    if (globalCurrentTable == TableOption::Menu)
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
    else if (globalCurrentTable == TableOption::GuessingGame)
    {
        std::cout
            << "\n=== Table: Guess The Sum ===\n"
            << "1) Play a round\n"
            << "2) Change bet\n"
            << "3) Show rules\n"
            << "4) Leave table\n"
            << "Choice: ";
    }
    else if (globalCurrentTable == TableOption::OddOrEven)
    {
        std::cout
            << "\n=== Table: Odd or Even ===\n"
            << "1) Play a round\n"
            << "2) Change bet\n"
            << "3) Show rules\n"
            << "4) Leave table\n"
            << "Choice: ";
    }
    else if (globalCurrentTable == TableOption::SpinTheWheel)
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

void ShowRules()
{
    if (globalCurrentTable == TableOption::GuessingGame)
    {
        std::cout
            << "\n--- Rules: Guess The Sum ---\n"
            << "Guess the sum of two dice (2-12).\n"
            << "Two dice are rolled and shown, plus the total.\n"
            << "Wrong guess: you lose your bet.\n"
            << "Payout: 5x on correct guess.\n";
    }
    else if (globalCurrentTable == TableOption::OddOrEven)
    {
        std::cout
            << "\n--- Rules: Odd or Even ---\n"
            << "Pick Odd (1) or Even (2). Two dice are rolled and shown.\n"
            << "Win if both dice are odd when you picked Odd, or both even when you picked Even.\n"
            << "Mixed parity means the house wins. Sum does not matter.\n"
            << "Payout: 2x on win, otherwise you lose your bet.\n";
    }
    else if (globalCurrentTable == TableOption::SpinTheWheel)
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

void ShowStats() 
{
    std::cout << "\nYour five most recent games: \n";

    for (int i = 0; i < 5; i++)
    {
        std::cout << i + 1 << ": ";

        if (globalStatArr[i] == -1)
        {
            std::cout << "Loss";
        }
        else if (globalStatArr[i] == 1)
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
void EvaluateTableEarnings() 
{
    int tableIndex = static_cast<int>(globalCurrentTable);

    int maxEarning = 400;
    int minEarning = -150;

    if (globalMoneyArr[tableIndex - 1] == 0) // first time
    {
        std::cout << "\nThe dealer greets you with a sly smile.\n";
        system("pause");
    }
    else if (globalMoneyArr[tableIndex - 1] > maxEarning)
    {
        std::cout
            << "\nYou've been on fire at this table, winning far too much...\n"
            << "The pit boss whispers to the guards, and they politely escort you away.\n"
            << "You are no longer welcome at this table.\n";
        system("pause");
        MainMenu();
    }
    else if (globalMoneyArr[tableIndex - 1] < minEarning)
    {
        std::cout
            << "\nThis table has not been kind to you...\n"
            << "The dealer smirks as your losses keep piling up.\n"
            << "Maybe it's time to try your luck somewhere else.\n";
        system("pause");
    }
    else 
    {
        std::cout 
            << "\nYour streak here has been mixed, some wins, some losses.\n"
            << "The dealer greets you with a sly smile.\n";
        system("pause");
    }

}

void EnterTable(TableOption tableToEnter)
{
    globalCurrentTable = tableToEnter;
    EvaluateTableEarnings();

    while (globalCurrentTable == tableToEnter)
    {
        ShowPersonalDetails();
        ShowOptions();

        GameAction action = static_cast<GameAction>(ReadIntInRange(1, 4));

        switch (action)
        {
        case GameAction::Play:
        {
            if (globalCurrentTable == TableOption::GuessingGame)
            {
                PlayGuessingRound();
            }
            if (globalCurrentTable == TableOption::OddOrEven)
            {
                PlayOddEvenRound();
            }
            if (globalCurrentTable == TableOption::SpinTheWheel)
            {
                PlaySpinWheelRound();
            }
            HandleBankruptcy();
            break;
        }
        case GameAction::ChangeBet:
        {
            ChangeBet();
            break;
        }
        case GameAction::ShowRules:
        {
            ShowRules();
            break;
        }
        case GameAction::LeaveTable:
        {
            globalCurrentTable = TableOption::Menu;
            break;
        }
        default: break;
        }
    }
}

// ---------- Guessing Game ----------
void PlayGuessingRound()
{
    std::cout << "\nEnter your guess (2-12): ";
    int guess = ReadIntInRange(2, 12);

    int diceOne = RollDice();
    int diceTwo = RollDice();
    int sum = diceOne + diceTwo;

    std::cout << "\nDice 1: " << diceOne << ", Dice 2: " << diceTwo << "  -> Sum: " << sum << "\n";

    if (guess == sum)
    {
        int win = globalBet * 5;
        globalMoney += win;
        globalMoneyArr[0] += win;
        std::cout << "BINGO! Your payout: " << win << " kr.\n";
        UpdateStats(true);
    }
    else
    {
        globalMoney -= globalBet;
        globalMoneyArr[0] -= globalBet;
        std::cout << "Miss! You lose " << globalBet << " kr.\n";
        UpdateStats(false);
    }
    system("pause");
}

// ---------- Odd or Even ----------
void PlayOddEvenRound()
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
        int win = globalBet * 2;
        globalMoney += win;
        globalMoneyArr[1] += win;
        std::cout << "You win! Your payout: " << win << " kr.\n";
        UpdateStats(true);
    }
    else
    {
        globalMoney -= globalBet;
        globalMoneyArr[1] -= globalBet;
        std::cout << "House wins. You lose " << globalBet << " kr.\n";
        UpdateStats(false);
    }
    system("pause");
}

// ---------- Spin the wheel ----------
void PlaySpinWheelRound() 
{
    std::cout << "\nSpin The Wheel (1):  ";
    int pick = ReadIntInRange(1, 1);

    int dice1 = RollDice();
    int dice2 = RollDice();
    int dice3 = RollDice();

    std::cout << dice1 << " | " <<  dice2 << " | " << dice3 << "\n";

    int win = globalBet;

    if (dice1 == dice2 && dice2 == dice3) {

        win *= 40;
        globalMoney += win;
        globalMoneyArr[2] += win;
        std::cout << "<--- 40X WIN! --->\n";
        std::cout << "Your payout: " << win << " kr.\n";
        UpdateStats(true);

    }
    else if ((dice1 == dice2) || (dice2 == dice3) || (dice3 == dice1)) {

        win *= 2;
        globalMoney += win;
        globalMoneyArr[2] += win;
        std::cout << "<--- 2X WIN! --->\n";
        std::cout << "Your payout: " << win << " kr.\n";
        UpdateStats(true);
    }
    else {
        globalMoney -= globalBet;
        globalMoneyArr[2] -= globalBet;
        std::cout << "House wins. You lose " << globalBet << " kr.\n";
        UpdateStats(false);
    }
    system("pause");
}

// ---------- Main ----------
void MainMenu()
{
    globalCurrentTable = TableOption::Menu;

    while (globalCurrentTable == TableOption::Menu)
    {
        ShowPersonalDetails();
        ShowOptions();

        TableOption table = static_cast<TableOption>(ReadIntInRange(1, 5));

        switch (table)
        {
        case TableOption::GuessingGame:
        {
            EnterTable(TableOption::GuessingGame);
            break;
        }
        case TableOption::OddOrEven:
        {
            EnterTable(TableOption::OddOrEven);
            break;
        }
        case TableOption::SpinTheWheel:
        {
            EnterTable(TableOption::SpinTheWheel);
            break;
        }
        case TableOption::Stats:
        {
            ShowStats();
            system("pause");
            break;
        }
        case TableOption::Quit:
        {
            std::cout << "\nYou leave with " << globalMoney << " kr. Come back soon!\n";
            globalCurrentTable = TableOption::Quit;
            break;
        }
        default: break;
        }
    }
}

int main()
{
    ShowIntro();
    MainMenu();
    return 0;
}
