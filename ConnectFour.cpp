#include <iostream>

using namespace std;

void TurnCounter();
void UpdateCheckboard();
void PlaceTheChess();
void CheckboardInitialize();
int Referee();
int currentTurn = 0;
int checkboard[6][7];

int main()
{
	while (1)
	{
		TurnCounter();
		UpdateCheckboard();
		PlaceTheChess();
	}
	Referee();
	return 0;
	system("PAUSE");
}

void TurnCounter()
{
	cout << "Now it is the turn " << currentTurn+1 << "." << endl;
}

void CheckboardInitialize()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			checkboard[i][j] = 0;
		}
	}
}

void UpdateCheckboard()
{
	if (currentTurn == 0)
	{
		CheckboardInitialize();
		cout << "1 2 3 4 5 6 7" << endl;
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if (checkboard[i][j] == 0)
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
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					if (checkboard[i][j] == 0)
						cout << ". ";

					if (checkboard[i][j] == 1)
						cout << "O ";

					if (checkboard[i][j] == 2)
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
	currentTurn += 1;
	if (currentTurn % 2 == 0)
	{
		cout << "Player O's turn! Type the column number to insert a piece: " << endl;
		cin >> column;
		column = column - 1;
		int i = 5;
		while (i >= 0)
		{
			if (checkboard[i][column] == 0)
			{
				checkboard[i][column] = 1;
				i = -1;
			}
			if (checkboard[i][column] != 0)
			{
				i--;
			}
		}
	}
	if (currentTurn % 2 == 1)
	{
		cout << "Player X's turn! Type the column number to insert a piece: " << endl;
		cin >> column;
		column = column - 1;
		int i = 5;
		while (i >= 0)
		{
			if (checkboard[i][column] == 0)
			{
				checkboard[i][column] = 2;
				i = -1;
			}
			if (checkboard[i][column] != 0)
			{
				i--;
			}
		}
	}
}

int Referee()
{
	int raw;
	int col;
	int Ocounter = 0;
	int Xcounter = 0;
	//check line
	for (raw = 5; raw >= 0; raw--)
	{
	}

	if (Ocounter != 4 && Xcounter != 4)
		return 0;
	if (Ocounter == 4)
		return 1;
	if (Xcounter == 4)
		return 2;
}



