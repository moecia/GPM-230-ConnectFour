//Project name: GAME-230-Project#2-Connect Four
//Author: Bingnan Li, Nathan				  
//Created Date: 10/05/2017	
//Last Modified Date: 10/07/2017
//Version: Finished, Normal Mode + Hard Mode I & K

#include <iostream>
#include <algorithm>


#define P_O 1
#define P_X 2
#define DRAW 3

#define NORMALMODE 10
#define CUSTOMMODE 11
#define MODIFIEDCONNECTFOUR 12

using namespace std;

void ModeSelect();
void TurnCounter();
void UpdateCheckerboard();			//Update the 'Looking' of the checkerboard
void PlaceTheChess(int &last_row, int &last_col);
int CheckerboardUpdater(int);		//Update the actual value which presented chest in the checkerboard
void CheckerboardInitialize();
bool isColFull(int);			//Check the column which player input is avaiable or not
void Referee(int last_row, int last_col);
void Restart(int);
int ColumnTranslator(char);
void RemoveApiece(int &lastCol);
void RefereeForRemoveApiece(int lastCol);
void CheckerboardUpdaterForRemoveApiece(int);
bool ButtomCheckForRemoveAPiece();

int currentTurn = 0;
int ** checkerboard;
int MAXROW = -1;
int MAXCOL = -1;
int requiredToWin = -1;
int currentMode = -1;

int main()
{
	int last_row;
	int last_col;
	int colToRemove;
	ModeSelect();
	CheckerboardInitialize();
	while (1)
	{
		if (currentMode == NORMALMODE)
		{
			TurnCounter();
			UpdateCheckerboard();
			PlaceTheChess(last_row, last_col);
			Referee(last_row, last_col);
			system("cls");
		}

		if (currentMode == CUSTOMMODE)
		{
			TurnCounter();
			if (MAXCOL >= 10)
				cout << "Note: Input 10 = A, 11 = B, 12 = C, 13 = D, 14 = E, 15 = F, 16 = G, 17 = H, 18 = I, 19 = J, 20 = K." << endl;
			UpdateCheckerboard();
			PlaceTheChess(last_row, last_col);
			Referee(last_row, last_col);
			system("cls");
		}

		if (currentMode == MODIFIEDCONNECTFOUR)
		{
			int addOrRemove = -1;
			bool ableToRemove = false;
			TurnCounter();
			UpdateCheckerboard();
			while (addOrRemove == -1)
			{
				cout << "Do you want remove a piece of yours from the bottom? (Enter 1 if you want, 0 if you don't)" << endl;
				cin >> addOrRemove;
			}
			if (addOrRemove == 0)
			{
				PlaceTheChess(last_row, last_col);
				Referee(last_row, last_col);
			}
			if (addOrRemove == 1)
			{
				ableToRemove = ButtomCheckForRemoveAPiece();
				if (ableToRemove == true)
				{
					RemoveApiece(colToRemove);
					RefereeForRemoveApiece(colToRemove);
				}
				else
				{
					cout << "You do not have any piece in the buttom" << endl;
					PlaceTheChess(last_row, last_col);
					Referee(last_row, last_col);
				}
			}
			system("cls");
		}
	}
	return 0;
	system("PAUSE");
}

void ModeSelect()
{
	cout << "Mode #1(Enter 10): Normal Mode - Regular Connect Four." << endl;
	cout << "Mode #2(Enter 11): Custom Mode - You can decide the number of colums, rows, and number of pieces lined up that required to win." << endl;
	cout << "Mode #3(Enter 12): Modified Connect Four - Players are able to remove one of their own peices from the BOTTOM of the gird" << endl;
	while (currentMode < 10 || currentMode > 12)
	{
		cout << "Please select a mode£º ";
		cin >> currentMode;
	}	
	if (currentMode == NORMALMODE)
	{
		MAXROW = 6;
		MAXCOL = 7;
		requiredToWin = 4;
	}
	if(currentMode == MODIFIEDCONNECTFOUR)
	{
		MAXROW = 6;
		MAXCOL = 7;
		requiredToWin = 4;
	}
	if (currentMode == CUSTOMMODE)
	{
		while (MAXROW < 4 || MAXROW > 20)
		{
			cout << "How many rows you want? (Between 4 and 20)" << endl;
			cin >> MAXROW;
		}

		while (MAXCOL < 4 || MAXCOL > 20)
		{
			cout << "How many cols you want? (Between 4 and 20)" << endl;
			cin >> MAXCOL;
		}

		while (requiredToWin < 3 || requiredToWin > max(MAXROW, MAXCOL))
		{
			cout << "How many requiredToWin you want? (Between 3 and 20)" << endl;
			cin >> requiredToWin;
		}
		
	}
}

void TurnCounter()
{
	cout << endl;
	if(currentTurn % 2 == 1)
		cout << "Turn " << currentTurn + 1 << ". Now it is the O's turn." << endl;
	if (currentTurn % 2 == 0)
		cout << "Turn " << currentTurn + 1 << ". Now it is the X's turn." << endl;
}

void CheckerboardInitialize()
{
	checkerboard = new int* [MAXROW];
	for (int i = 0; i < MAXROW; i++)
		checkerboard[i] = new int[MAXCOL];

	for (int row = 0; row < MAXROW; row++)
	{
		for (int col = 0; col < MAXCOL; col++)
		{
			checkerboard[row][col] = 0;
		}
	}
}

void UpdateCheckerboard()
{
	for (int i = 1; i <= MAXCOL; i++)
	{
		if (i < 10)
			cout << i << " ";
		else
			cout << char('A' + i - 10) << " ";
	}
	cout << endl;

	for (int row = 0; row < MAXROW; row++)
	{
		for (int col = 0; col < MAXCOL; col++)
		{
			if (checkerboard[row][col] == 0)
				cout << ". ";

			if (checkerboard[row][col] == 1)
				cout << "O ";

			if (checkerboard[row][col] == 2)
				cout << "X ";
		}
		cout << "\n";
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
			//column = ColumnTranslator(column);
			column = column - 1;
			last_col = column;
			isColumnAvailable = isColFull(column);

			if (column >= MAXCOL || column < 0)
				cout << "You input a wrong column, please input again!" << endl;

			if (isColumnAvailable == false && (column < MAXCOL && column > 0))
				cout << "This column is full, please try another column." << endl;

			if (column < MAXCOL && isColumnAvailable == true)
			{
				last_row = CheckerboardUpdater(column);
				i = 0;
			}
		}

		if (currentTurn % 2 == 1)
		{
			cout << "Player X's turn! Type the column number to insert a piece: " << endl;
			cin >> column;
			//column = ColumnTranslator(column);
			column = column - 1;
			last_col = column;
			isColumnAvailable = isColFull(column);

			if (column >= MAXCOL || column < 0)
				cout << "You input a wrong column, please input again!" << endl;

			if (isColumnAvailable == false && (column < MAXCOL && column > 0))
				cout << "This column is full, please try another column." << endl;

			if (column < MAXCOL && isColumnAvailable == true)
			{
				last_row = CheckerboardUpdater(column);
				i = 0;
			}
		}
	}
	
	
}

int CheckerboardUpdater(int col)
{
	int row = MAXROW - 1;
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

bool isColFull(int col)
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
	for (int c = last_col + 1; c < MAXCOL; c++)
	{
		if (checkerboard[last_row][c] != currentPiece)
			break;
		rowCount++;
	}
	if (rowCount >= requiredToWin)
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
	for (int r = last_row + 1; r < MAXROW; r++)
	{
		if (checkerboard[r][last_col] != currentPiece)
			break;
		colCount++;
	}
	if (colCount >= requiredToWin)
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
	for (int r = last_row + 1, c = last_col + 1; c <= MAXCOL - 1 && r <= MAXROW -1; c++, r++)
	{
		if (checkerboard[r][c] != currentPiece)
			break;
		leftDiagonalCount++;
	}
	if (leftDiagonalCount >= requiredToWin)
	{
		Restart(currentPiece);
	}
	//Check Right Diagonal - "/"
	int rightDiagonalCount = 1;
	for (int r = last_row - 1 , c = last_col + 1; c <= MAXCOL -1  && r >= 0; c++, r--)
	{
		if (checkerboard[r][c] != currentPiece)
			break;
		rightDiagonalCount++;
	}
	for (int r = last_row + 1, c = last_col - 1; c >= 0 && r <= MAXROW - 1; c--, r++)
	{
		if (checkerboard[r][c] != currentPiece)
			break;
		rightDiagonalCount++;
	}
	if (rightDiagonalCount >= requiredToWin)
	{
		Restart(currentPiece);
	}
	//Draw
	if (currentTurn == 42)
		Restart(DRAW);
}

void Restart(int endStat)
{
	int isPlayAgain = -1;
	switch (endStat)
	{
		case P_X:
			cout << "X win the Game!" << endl;
			UpdateCheckerboard();
			break;
		case P_O:
			cout << "O win the Game!" << endl;
			UpdateCheckerboard();
			break;
		case DRAW:
			cout << "Draw!" << endl;
			UpdateCheckerboard();
			break;
	}
	while (isPlayAgain != 1 && isPlayAgain != 0)
	{
		cout << "Play again? Input 1 for play again, 0 for exit the game." << endl;
		cin >> isPlayAgain;
	}
	if (isPlayAgain == 1)
	{		
		for (int i = 0; i < MAXROW; i++)
			delete checkerboard[i];

		delete checkerboard;
		checkerboard = NULL;

		currentTurn = 0;
		currentMode = -1;
		MAXROW = -1;
		MAXCOL = -1;
		requiredToWin = -1;
		main();
	}

	if (isPlayAgain == 0)
	{
		exit(0);
	}
}

int ColumnTranslator(char col)
{
	if ('1' <= col && col <= '9')
		return int(col - '1' + 1);
	if ('A' <= col && col <= 'A' + MAXCOL - 10)
		return int(col - 'A' + 10);
}

void RemoveApiece(int &lastCol)
{
	char column;
	bool isColumnAvailable;
	currentTurn += 1;
	int i = 1;
	while (i == 1)
	{
		if (currentTurn % 2 == 0)
		{
			cout << "Player O's turn! Type the column number to remove a piece from the bottom: " << endl;
			cin >> column;
			column = ColumnTranslator(column);
			column = column - 1;
			lastCol = column;

			if (column >= MAXCOL || column < 0)
				cout << "You input a wrong column, please input again!" << endl;

			if (checkerboard[MAXROW-1][column] != P_O && (column < MAXCOL && column > 0))
				cout << "You do not have a piece in the buttom of this column." << endl;

			if (column < MAXCOL && checkerboard[MAXROW - 1][column] == P_O )
			{
				CheckerboardUpdaterForRemoveApiece(column);
				i = 0;
			}
		}

		if (currentTurn % 2 == 1)
		{
			cout << "Player X's turn! Type the column number to remove a piece from the bottom: " << endl;
			cin >> column;
			column = ColumnTranslator(column);
			column = column - 1;
			lastCol = column;

			if (column >= MAXCOL || column < 0)
				cout << "You input a wrong column, please input again!" << endl;

			if (checkerboard[MAXROW - 1][column] != P_X  && (column < MAXCOL && column > 0))
				cout << "You do not have a piece in the buttom of this column." << endl;

			if (column < MAXCOL && checkerboard[MAXROW - 1][column] == P_X)
			{
				CheckerboardUpdaterForRemoveApiece(column);
				i = 0;
			}
		}
	}
}

void RefereeForRemoveApiece(int lastCol)
{
	if (currentTurn <= 3)
		return;
	// get the current player
	for (int i = MAXROW - 1; i >= 0; i--)
	{
		int currentPiece = checkerboard[i][lastCol];

		// row
		int rowCount = 1;
		for (int c = lastCol - 1; c >= 0; c--)
		{
			if (checkerboard[i][c] != currentPiece)
				break;
			rowCount++;
		}
		for (int c = lastCol + 1; c < MAXCOL; c++)
		{
			if (checkerboard[i][c] != currentPiece)
				break;
			rowCount++;
		}
		if (rowCount >= requiredToWin)
		{
			Restart(currentPiece);
		}
		// col
		int colCount = 1;
		for (int r = i - 1; r >= 0; r--)
		{
			if (checkerboard[r][lastCol] != currentPiece)
				break;
			colCount++;
		}
		for (int r = i + 1; r < MAXROW; r++)
		{
			if (checkerboard[r][lastCol] != currentPiece)
				break;
			colCount++;
		}
		if (colCount >= requiredToWin)
		{
			Restart(currentPiece);
		}

		//Check Left Diagonal - "\"
		int leftDiagonalCount = 1;
		for (int r = i - 1, c = lastCol - 1; c >= 0 && r >= 0; c--, r--)
		{
			if (checkerboard[r][c] != currentPiece)
				break;
			leftDiagonalCount++;
		}
		for (int r = i + 1, c = lastCol + 1; c <= MAXCOL - 1 && r <= MAXROW - 1; c++, r++)
		{
			if (checkerboard[r][c] != currentPiece)
				break;
			leftDiagonalCount++;
		}
		if (leftDiagonalCount >= requiredToWin)
		{
			Restart(currentPiece);
		}
		//Check Right Diagonal - "/"
		int rightDiagonalCount = 1;
		for (int r = i - 1, c = lastCol + 1; c <= MAXCOL - 1 && r >= 0; c++, r--)
		{
			if (checkerboard[r][c] != currentPiece)
				break;
			rightDiagonalCount++;
		}
		for (int r = i + 1, c = lastCol - 1; c >= 0 && r <= MAXROW - 1; c--, r++)
		{
			if (checkerboard[r][c] != currentPiece)
				break;
			rightDiagonalCount++;
		}
		if (rightDiagonalCount >= requiredToWin)
		{
			Restart(currentPiece);
		}
	}
	//Draw
	if (currentTurn == 42)
		Restart(DRAW);
}

void CheckerboardUpdaterForRemoveApiece(int col)
{
	int row = MAXROW - 1;
	while (row >= 1)
	{
		checkerboard[row][col] = checkerboard[row - 1][col];
		row--;
	}
}

bool ButtomCheckForRemoveAPiece()
{
	if (currentTurn % 2 == 1) //Check O
	{
		for (int i = 0; i < MAXCOL; i++)
		{
			if (checkerboard[MAXROW - 1][i] == P_O)
				return true;
		}
		return false;
	}

	if (currentTurn % 2 == 0) //Check X
	{
		for (int i = 0; i < MAXCOL; i++)
		{
			if (checkerboard[MAXROW - 1][i] == P_X)
				return true;
		}
		return false;
	}
}