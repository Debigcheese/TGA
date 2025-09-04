// tictactoe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int row;
int col;
char arrBoard[3][3] = {'X',' X ',' X ',' X ',' X ',' X ',' X ',' X ',' X ', };
char playerTurn;
int p;

char ChangePlayerTurn() {
    if (p == 0) {
        
        p = 1;
        return 'O';
    }
    else {

        p = 0;
        return 'X';
    }
}

bool HasWon() {



    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {

            if (arrBoard[i][j] == 'X' && arrBoard[i][j+1] == 'X' && arrBoard[i][j+2] == 'X') {
                return true;
            }
            if (arrBoard[i][j] == 'X' && arrBoard[i][j + 1] == 'X' && arrBoard[i][j + 2] == 'X') {
                return true;
            }



        }

    }

}

int main()
{

    for (int i = 0; i < 7; i++) {
        std::cout << "\n";
        for (int j = 0; j < 7; j++) {

            if (i % 2 == 0) {
                std::cout << "--"; //floors
            } else if (j % 2 == 0) {
                std::cout << "|"; //walls
            }
            else {
                std::cout << " " << arrBoard[row][col] << " ";
            }
        }
        arrBoard[row][col] = playerTurn;
        playerTurn = ChangePlayerTurn();

    }

    std::cout << "Hello World!\n";
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
