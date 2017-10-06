//Project name: GAME-230-Project#2-Connect Four
//Author: Bingnan Li, Nathan				  
//Date: 10/05/2017								
//Version: Unfinished

#include <iostream>

#define P_O 1
#define P_X 2
#define DRAW 3
#define MAXROW 6
#define MAXCOL 7

using namespace std;

void TurnCounter();
void UpdateCheckerboard();			//Update the 'Looking' of the checkerboard
void PlaceTheChess(int &last_row, int &last_col);
int CheckerboardUpdater(int);		//Update the actual value which presented chest in the checkerboard
void CheckerboardInitialize();
bool ColumnChecker(int);			//Check the column which player input is avaiable or not
void Referee(int last_row, int last_col);
void Restart(int);

int currentTurn = 0;
int checkerboard[6][7];

int main()
{
	int last_row;
	int last_col;
	while (1)
	{
		TurnCounter();
		UpdateCheckerboard();
		PlaceTheChess(last_row, last_col);
		//cout << "row: " << last_row << ", col:" << last_col << endl;
		Referee(last_row, last_col);
		system("cls");
	}
	return 0;
	system("PAUSE");
}

void TurnCounter()
{
	cout << endl;
	cout << "Now it is the turn " << currentTurn + 1 << "." << endl;
}

void CheckerboardInitialize()
{
	for (int raw = 0; raw < 6; raw++)
	{
		for (int col = 0; col < 7; col++)
		{
			checkerboard[raw][col] = 0;
		}
	}
}

void UpdateCheckerboard()
{
	if (currentTurn == 0)
	{
		CheckerboardInitialize();
		cout << "1 2 3 4 5 6 7" << endl;
		for (int raw = 0; raw < 6; raw++)
		{
			for (int col = 0; col < 7; col++)
			{
				if (checkerboard[raw][col] == 0)
					cout << ". ";
			}
			cout << endl;
		}
	}
	if (currentTurn > 0)
	{
		int gameContinue = 3;
		if (gameContinue == 3)
		{
			cout << "1 2 3 4 5 6 7" << endl;
			for (int raw = 0; raw < 6; raw++)
			{
				for (int col = 0; col < 7; col++)
				{
					if (checkerboard[raw][col] == 0)
						cout << ". ";

					if (checkerboard[raw][col] == 1)
						cout << "O ";

					if (checkerboard[raw][col] == 2)
						cout << "X ";
				}
				cout << "\n";
			}
		}
	}
}

void PlaceTheChess(int &last_row, int &last_col)
{
	int column;
	bool isColumnAvailable;
	currentTurn += 1;

	int i = 1;
	while(i == 1)
	{
		if (currentTurn % 2 == 0)
		{
			cout << "Player O's turn! Type the column number to insert a piece: " << endl;
			cin >> column;
			column = column - 1;
			last_col = column;
			isColumnAvailable = ColumnChecker(column);

			if (column >= 7)
				cout << "You input a wrong column, please input again!" << endl;

			if (isColumnAvailable == false)
				cout << "This column is full, please try another column." << endl;

			if (column < 7 && isColumnAvailable == true)
			{
				last_row = CheckerboardUpdater(column);
				i = 0;
			}
		}

		if (currentTurn % 2 == 1)
		{
			cout << "Player X's turn! Type the column number to insert a piece: " << endl;
			cin >> column;
			column = column - 1;
			last_col = column;
			isColumnAvailable = ColumnChecker(column);

			if (column >= 7)
				cout << "You input a wrong column, please input again!" << endl;

			if (isColumnAvailable == false)
				cout << "This column is full, please try another column." << endl;

			if (column < 7 && isColumnAvailable == true)
			{
				last_row = CheckerboardUpdater(column);
				i = 0;
			}
		}
	}
	
	
}

int CheckerboardUpdater(int col)
{
	int row = 5;
	if (currentTurn % 2 == 0)
	{
		while (row >= 0)
		{
			if (checkerboard[row][col] == 0)
			{
				checkerboard[row][col] = 1;
				return row;
			}
			if (checkerboard[row][col] != 0)
			{
				row--;
			}
		}
	}

	if (currentTurn % 2 == 1)
	{
		while (row >= 0)
		{
			if (checkerboard[row][col] == 0)
			{
				checkerboard[row][col] = 2;
				return row;
			}
			if (checkerboard[row][col] != 0)
			{
				row--;
			}
		}
	}
}

bool ColumnChecker(int col)
{
	bool isColumnAvailable;
	if (checkerboard[0][col] == 0)
		isColumnAvailable = true;

	if (checkerboard[0][col] != 0)
		isColumnAvailable = false;

	return isColumnAvailable;
}

void Referee(int last_row, int last_col)
{
	if (currentTurn <= 3)
		return;
	// get the current player
	int currentPiece = checkerboard[last_row][last_col];
	
	// row
	int rowCount = 1;
	for (int c = last_col - 1; c >= 0; c--)
	{
		if (checkerboard[last_row][c] != currentPiece)
			break;
		rowCount++;
	}
	for (int c = last_col + 1; c < 7; c++)
	{
		if (checkerboard[last_row][c] != currentPiece)
			break;
		rowCount++;
	}
	if (rowCount >= 4)
	{
		Restart(currentPiece);
	}
	// col
	int colCount = 1;
	for (int r = last_row - 1; r >= 0; r--)
	{
		if (checkerboard[r][last_col] != currentPiece)
			break;
		colCount++;
	}
	for (int r = last_row + 1; r < 6; r++)
	{
		if (checkerboard[r][last_col] != currentPiece)
			break;
		colCount++;
	}
	if (colCount >= 4)
	{
		Restart(currentPiece);
	}

	//Check Left Diagonal - "\"
	int leftDiagonalCount = 1;
	for (int r = last_row - 1, c = last_col - 1; c >= 0 && r >= 0; c--, r--)
	{
		if (checkerboard[r][c] != currentPiece)
			break;
		leftDiagonalCount++;
	}
	for (int r = last_row + 1, c = last_col + 1; c <= 6 && r <= 5; c++, r++)
	{
		if (checkerboard[r][c] != currentPiece)
			break;
		leftDiagonalCount++;
	}
	if (leftDiagonalCount >= 4)
	{
		Restart(currentPiece);
	}
	//Check Right Diagonal - "/"
	int rightDiagonalCount = 1;
	for (int r = last_row - 1 , c = last_col + 1; c <= 6  && r >= 0; c++, r--)
	{
		if (checkerboard[r][c] != currentPiece)
			break;
		rightDiagonalCount++;
	}
	for (int r = last_row + 1, c = last_col - 1; c >= 0 && r <= 5; c--, r++)
	{
		if (checkerboard[r][c] != currentPiece)
			break;
		rightDiagonalCount++;
	}
	if (rightDiagonalCount >= 4)
	{
		Restart(currentPiece);
	}
	//Draw
	if (currentTurn == 42)
		Restart(DRAW);
}

void Restart(int endStat)
{
	int isPlayAgain;
	switch (endStat)
	{
		case P_X:
			cout << "X win the Game!" << endl;
			break;
		case P_O:
			cout << "O win the Game!" << endl;
			break;
		case DRAW:
			cout << "Draw!" << endl;
			break;
	}
	cout << "Play again? Input 1 for play again, 0 for exit the game." << endl;
	cin >> isPlayAgain;
	if (isPlayAgain == 1)
	{
		currentTurn = 0;
		for (int raw = 0; raw < 6; raw ++)
		{
			for (int col = 0; col == 7; col++)
				checkerboard[raw][col] = 0;
		}
	}

	if (isPlayAgain == 0)
	{
		exit(0);
	}
}


