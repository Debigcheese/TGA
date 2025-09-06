#include <iostream>
#include <random>

enum class TableOption
{
    Menu = 0,
    GuessingGame = 1,
    OddOrEven = 2,
    Quit = 3,
};

enum class GameAction
{
    Play = 1,
    ChangeBet = 2,
    ShowRules = 3,
    LeaveTable = 4,
};

static const int INITIAL_MONEY = 100;
static const int DEFAULT_BET = 10;
static const TableOption DEFAULT_TABLEOPTION = TableOption::Menu;

std::random_device g_rd;
std::mt19937 g_rng{ g_rd() };

int globalMoney = INITIAL_MONEY;
int globalBet = DEFAULT_BET;
TableOption globalCurrentTable;

int ReadIntInRange(int aMinValue, int aMaxValue);
int RollDice();
void ChangeBet();
void HandleBankruptcy();

// Print to console
void ShowIntro();
void ShowPersonalDetails();
void ShowOptions();
void ShowRules();

// Guessing Game
void PlayGuessingRound();
void GuessingTable();

// Odd or Even
void PlayOddEvenRound();
void OddEvenTable();

// Main
void MainMenu();

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
    if (globalMoney <= 0)
    {
        std::cout << "\nYou're out of money! Security drag you out of the casino.\n";
        globalCurrentTable = TableOption::Quit;
    }
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
            << "3) Leave casino\n"
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

}

void ShowRules()
{
    if (globalCurrentTable == TableOption::GuessingGame)
    {
        std::cout
            << "\n--- Rules: Guess The Sum ---\n"
            << "Guess the sum of two dice (2-12).\n"
            << "Two dice are rolled and shown, plus the total.\n"
            << "Payout: 5x on correct guess (you receive 5 * bet).\n"
            << "Wrong guess: you lose your bet.\n";
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
    system("pause");
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
        std::cout << "BINGO! Your payout: " << win << " kr.\n";
    }
    else
    {
        globalMoney -= globalBet;
        std::cout << "Miss! You lose " << globalBet << " kr.\n";
    }
    system("pause");
}

void GuessingTable()
{
    globalCurrentTable = TableOption::GuessingGame;

    while (globalCurrentTable == TableOption::GuessingGame)
    {
        ShowPersonalDetails();
        ShowOptions();

        GameAction action = static_cast<GameAction>(ReadIntInRange(1, 4));

        switch (action) 
        {
        case GameAction::Play:
        {
            PlayGuessingRound();
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
        std::cout << "You win! Your payout: " << win << " kr.\n";
    }
    else
    {
        globalMoney -= globalBet;
        std::cout << "House wins. You lose " << globalBet << " kr.\n";
    }
    system("pause");
}

void OddEvenTable()
{
    globalCurrentTable = TableOption::OddOrEven;

    while (globalCurrentTable == TableOption::OddOrEven)
    {
        ShowPersonalDetails();
        ShowOptions();

        GameAction action = static_cast<GameAction>(ReadIntInRange(1, 4));

        switch (action)
        {
        case GameAction::Play:
        {
            PlayOddEvenRound();
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

// ---------- Main ----------
void MainMenu()
{
    globalCurrentTable = TableOption::Menu;

    while (globalCurrentTable == TableOption::Menu)
    {
        ShowPersonalDetails();
        ShowOptions();

        TableOption table = static_cast<TableOption>(ReadIntInRange(1, static_cast<int>(TableOption::Quit)));

        switch (table)
        {
        case TableOption::GuessingGame:
        {
            GuessingTable();
            break;
        }
        case TableOption::OddOrEven:
        {
            OddEvenTable();
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
