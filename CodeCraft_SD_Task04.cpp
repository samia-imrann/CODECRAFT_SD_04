#include <iostream>
#include <fstream>
using namespace std;

const int SIZE = 9;
char board[SIZE][SIZE];

bool isValid(int row, int col, char num)
{
    for (int x = 0; x < SIZE; x++)
    {
        if (board[row][x] == num || board[x][col] == num)
            return false;
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[startRow + i][startCol + j] == num)
                return false;

    return true;
}

bool solveSudoku()
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            if (board[row][col] == '_')
            {
                for (char num = '1'; num <= '9'; num++)
                {
                    if (isValid(row, col, num))
                    {
                        board[row][col] = num;
                        if (solveSudoku())
                            return true;
                        board[row][col] = '_';
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void printBoard()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

void saveToFile(const string& filename)
{
    ofstream fout(filename);
    if (!fout) {
        cout << "Error writing to file.\n";
        return;
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            fout << board[i][j] << " ";
        fout << endl;
    }

    fout.close();
    cout << "Solved board saved to " << filename << endl;
}

void loadFromFile(const string& filename)
{
    ifstream fin(filename);
    if (!fin) {
        cout << "Error opening the file.\n";
        return;
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            fin >> board[i][j];
    }

    fin.close();
    cout << "Board loaded successfully from " << filename << endl;
}

int main()
{
    string filename;
    cout << "Enter file name from where you want to load board (with .txt extension): ";
    cin >> filename;

    loadFromFile(filename);

    cout << "\nInput Puzzle:\n";
    printBoard();

    if (solveSudoku())
    {
        cout << "\nSolved Puzzle:\n";
        printBoard();
        saveToFile("solved_sudoku.txt");
    }
    else
    {
        cout << "\nNo solution exists.\n";
    }

    return 0;
}
