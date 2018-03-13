// C++ Program to compute evaluation function for
// Tic Tac Toe Game.

#include <stdio.h>
#include <algorithm>
using namespace std;

// Returns a value based on who is winning
// b[3][3] is the Tic-Tac-Toe board
int evaluate(char b[3][3]) {
	// Checking Rows for X or O victory
	for (int row = 0; row < 3; ++row) {
		if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
			if (b[row][0] == 'X')
				return +10;
			else if (b[row][0] == 'O')
				return -10;
		}
	}

	// Checking Columns for X or O victory
	for (int col = 0; col < 3; ++col) {
		if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
			if (b[0][col] == 'X')
				return +10;
			else if (b[0][col] == 'Y')
				return -10;
		}
	}

	// Checking Diagonals for X or O victory
	if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
		if (b[0][0] == 'X')
			return +10;
		else if (b[0][0] == 'Y')
			return -10;
	}

	if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
		if (b[0][2] == 'X')
			return +10;
		else if (b[0][2] == 'Y')
			return -10;
	}

	// Else if none of them have won return 0
	return 0;
}

// Driver code
int main() {
	char board[3][3] = 
	{
		{'X', ' ', 'O'},
		{' ', 'X', 'O'},
		{' ', ' ', 'X'}
	};

	int value = evaluate(board);
	printf("The value of this board is %d\n", value);

	return 0;
}
