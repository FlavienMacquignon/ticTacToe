#include <iostream>
#include <string>

using namespace std;
struct Move
{
    int line, columns;
};
//Return the number of remainings turn based on the number of lest boxes
int remainingsTurns(char grid[3][3])
{
    int remainingTurn = 0;
    for (int k = 0; k < 3; k++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (grid[k][i] == ' ')
            {
                remainingTurn++;
            }
        }
    }
    return remainingTurn;
}
//Print the grid on screen
void printGrid(char grid[3][3])
{
    for (int k = 0; k < 3; k++)
    {
        for (int i = 0; i < 3; i++)
        {
            cout << "| " << grid[k][i] << " ";
        }

        cout << "|" << endl;
    }

}
//Give a value to the board
int evaluateBoard(char grid[3][3])
{
    //Check the board for lines
    for (int k = 0; k < 3; k++)
    {
        if (grid[k][0] == grid[k][1] && grid[k][1] == grid[k][2])
        {
            if (grid[k][0] == 'x')
            {
                return +10;
            }
            else if (grid[k][0] == 'o')
            {
                return -10;
            }
        }
    }

    //Check the board for columns
    for (int k = 0; k < 3; k++)
    {
        if (grid[0][k] == grid[1][k] && grid[1][k] == grid[2][k])
        {
            if (grid[0][k] == 'x')
            {
                return +10;
            }
            else if (grid[0][k] == 'o')
            {
                return -10;
            }
        }
    }

    //Check the board for diagonals
    if (grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2])
    {
        if (grid[0][0] == 'x')
        {
            return +10;
        }
        else if (grid[0][0] == 'o')
        {
            return -10;
        }
    }
    if (grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0])
    {
        if (grid[0][2] == 'x')
        {
            return +10;
        }
        else if (grid[0][2] == 'o')
        {
            return -10;
        }
    }
    //if no ictory return 0
    return 0;
}
// MiniMax algorithm
int miniMax(char grid[3][3], int turn, bool maxMove)
{
    int score = evaluateBoard(grid);
    
    if (score == 10)
    {
        return score;
    }
    if (score == -10)
    {
        return score;
    }
    //Check if the game is a tie
    if (remainingsTurns(grid) == 0)
    {
        return 0;
    }
    if (maxMove)
    {
        int best = -1000;
        for (int k = 0; k < 3; k++)
        {
            for (int i = 0; i < 3; i++)
            {
                if (grid[k][i] == ' ')
                {
                    grid[k][i] = 'x';
                    best = max(best, miniMax(grid, turn + 1, !maxMove));
                    grid[k][i] = ' ';

                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;
        for (int k = 0; k < 3; k++)
        {
            for (int i = 0; i < 3; i++)
            {
                if (grid[k][i] == ' ')
                {
                    grid[k][i] = 'o';
                    best = min(best, miniMax(grid, turn + 1, !maxMove));
                    grid[k][i] = ' ';
                }
            }
        }
        return best;
    }
}

Move playerMov(char grid[3][3])
{
    Move playerMove;
    int input = -1;
    cout << "Enter the column you want to play (1, 2 or 3)" << endl;
    cin >> input;
    if (input == 1 || input == 2 || input == 3)
    {
        playerMove.columns = input-1;
        input = -1;
    }
    else
    {
        cout << "Error, enter a valid number!" << endl;
        return playerMov(grid);

    }
    cout << "Enter the line you want to play (1, 2 or 3)" << endl;
    cin >> input;
    if (input == 1 || input == 2 || input == 3)
    {
        playerMove.line = input-1;
        input = -1;
    }
    else
    {
        cout << "Error, enter a valid number!" << endl;
       return playerMov(grid);

    }
    return playerMove;

}
//return the best move using the MiniMax
Move findMove(char grid[3][3])
{
    int best = -1000;
   
    Move move;
    move.line = -1;
    move.columns = -1;
    //Check all move to find if this move is the best possible move
    for (int k = 0; k < 3; k++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (grid[k][i] == ' ')
            {
                grid[k][i] = 'x';
                int moveValue = miniMax(grid, 0, false);
                grid[k][i] = ' ';
                if (moveValue > best)
                {
                    best = moveValue;
                    move.line = k;
                    move.columns = i;
                }
            }
        }
    }
    return move;
}
int main()
{
    char grid[3][3];
    Move playerMove, algoMove;
    for (int k = 0; k < 3; k++)
    {
        for (int i = 0; i < 3; i++)
        {
            grid[k][i] = ' ';
        }
    }

    cout << "Welcome to the unbeatable Tic Tac Toe !" << endl;
    do
    {
        printGrid(grid);
        playerMove = playerMov(grid);
        grid[playerMove.line][playerMove.columns] = 'o';
        Move computerMove = findMove(grid);
        grid[computerMove.line][computerMove.columns] = 'x';
        

    } while (remainingsTurns(grid)>0);
    cout << endl;
}