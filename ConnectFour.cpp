//Project name: GAME-230-Project#2-Connect Four
//Author: Bingnan Li, Nathan				  
//Date: 10/05/2017								
//Version: Unfinished

#include <iostream>

using namespace std;

void TurnCounter();
void UpdateCheckerboard();			//Update the 'Looking' of the checkerboard
void PlaceTheChess();
void CheckerboardUpdater(int);		//Update the actual value which presented chest in the checkerboard
void CheckerboardInitialize();
bool ColumnChecker(int);			//Check the column which player input is avaiable or not
void Referee();
void Restart(int);

int currentTurn = 0;
int checkerboard[6][7];

int main()
{
	while (1)
	{
		TurnCounter();
		UpdateCheckerboard();
		PlaceTheChess();
		Referee();
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

void PlaceTheChess()
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
			isColumnAvailable = ColumnChecker(column);

			if (column >= 7)
				cout << "You input a wrong column, please input again!" << endl;

			if (isColumnAvailable == false)
				cout << "This column is full, please try another column." << endl;

			if (column < 7 && isColumnAvailable == true)
			{
				CheckerboardUpdater(column);
				i = 0;
			}
		}

		if (currentTurn % 2 == 1)
		{
			cout << "Player X's turn! Type the column number to insert a piece: " << endl;
			cin >> column;
			column = column - 1;
			isColumnAvailable = ColumnChecker(column);

			if (column >= 7)
				cout << "You input a wrong column, please input again!" << endl;

			if (isColumnAvailable == false)
				cout << "This column is full, please try another column." << endl;

			if (column < 7 && isColumnAvailable == true)
			{
				CheckerboardUpdater(column);
				i = 0;
			}
		}
	}
	
	
}

void CheckerboardUpdater(int col)
{
	int raw = 5;
	if (currentTurn % 2 == 0)
	{
		while (raw >= 0)
		{
			if (checkerboard[raw][col] == 0)
			{
				checkerboard[raw][col] = 1;
				raw = -1;
			}
			if (checkerboard[raw][col] != 0)
			{
				raw--;
			}
		}
	}

	if (currentTurn % 2 == 1)
	{
		while (raw >= 0)
		{
			if (checkerboard[raw][col] == 0)
			{
				checkerboard[raw][col] = 2;
				raw = -1;
			}
			if (checkerboard[raw][col] != 0)
			{
				raw--;
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

void Referee()
{
	int Ocounter = 0;
	int Xcounter = 0;
	if (currentTurn > 3)
	{
		//Check Raw
		for (int raw = 5; raw >= 0; raw--)
		{
			for (int col = 0; col < 7; col++)
			{
				if (Xcounter == 3)
					Restart(0);
				if (Ocounter == 3)
					Restart(1);

				if (checkerboard[raw][col] == 1 && checkerboard[raw][col - 1] == 1 && checkerboard[raw][col + 1] == 1)
					Ocounter += 1;
				if (checkerboard[raw][col] == 2 && checkerboard[raw][col - 1] == 2 && checkerboard[raw][col + 1] == 2)
					Xcounter += 1;
			}
		}

		Ocounter = 0;
		Xcounter = 0;
		//Check Col
		for (int col = 0; col < 7; col++)
		{
			for (int raw = 5; raw >= 0; raw--)
			{
				if (Xcounter == 3)
					Restart(0);
				if (Ocounter == 3)
					Restart(1);

				if (checkerboard[raw][col] == 1 && checkerboard[raw-1][col] == 1 && checkerboard[raw + 1][col] == 1)
					Ocounter += 1;
				if (checkerboard[raw][col] == 2 && checkerboard[raw-1][col] == 2 && checkerboard[raw + 1][col] == 2)
					Xcounter += 1;
			}
		}

		Ocounter = 0;
		Xcounter = 0;
		//Check Left Diagonal - "\"
		for (int raw = 5; raw >= 0; raw--)
		{
			for (int col = 0; col < 7; col++)
			{
				if (Xcounter == 3)
					Restart(0);
				if (Ocounter == 3)
					Restart(1);

				if (checkerboard[raw][col] == 1 && checkerboard[raw - 1][col - 1] == 1 && checkerboard[raw + 1][col + 1] == 1)
					Ocounter += 1;
				if (checkerboard[raw][col] == 2 && checkerboard[raw - 1][col - 1] == 2 && checkerboard[raw + 1][col + 1] == 2)
					Xcounter += 1;
			}
		}
		//Check Right Diagonal - "/"
		Ocounter = 0;
		Xcounter = 0;
		for (int raw = 5; raw >= 0; raw--)
		{
			for (int col = 0; col < 7; col++)
			{
				if (Xcounter == 3)
					Restart(0);
				if (Ocounter == 3)
					Restart(1);

				if (checkerboard[raw][col] == 1 && checkerboard[raw - 1][col + 1] == 1 && checkerboard[raw + 1][col - 1] == 1)
					Ocounter += 1;
				if (checkerboard[raw][col] == 2 && checkerboard[raw - 1][col + 1] == 2 && checkerboard[raw + 1][col - 1] == 2)
					Xcounter += 1;
			}
		}
	}


	if (currentTurn == 42)
		Restart(2);
}

void Restart(int endStat)
{
	int isPlayAgain;
	switch (endStat)
	{
		case 0:
			cout << "X win the Game!" << endl;
			break;
		case 1:
			cout << "O win the Game!" << endl;
			break;
		case 2:
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


