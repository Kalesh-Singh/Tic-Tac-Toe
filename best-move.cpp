// C++ Program to findthe optimal move
// for a player
# define DEBUG

#include <stdio.h>
#include <algorithm>
using namespace std;

#define SIDE 3

typedef struct {
	int row, col;
} Move;

char player = 'X', opponent = 'O';

// A function to show the correct board status
void showBoard(char board[][SIDE]) {
	printf("\n");

	printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
	printf("\t\t\t-----------\n");
	printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
	printf("\t\t\t-----------\n");
	printf("\t\t\t %c | %c | %c \n\n\n", board[2][0], board[2][1], board[2][2]);

	return;
}

// This function returns true if there are moves remaining
// on the board. It returns false if there are no moves left
// to play.

bool isMovesLeft(char board[3][3]) {
	for (int i = 0; i < 3; ++i) 
		for (int j = 0; j < 3; ++j )
			if (board[i][j] == ' ')
				return true;
	return false;
}

// This is the evaluation function as written previously
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
			else if (b[0][col] == 'O')
				return -10;
		}
	}

	// Checking Diagonals for X or O victory
	if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
		if (b[0][0] == 'X')
			return +10;
		else if (b[0][0] == 'O')
			return -10;
	}

	if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
		if (b[0][2] == 'X')
			return +10;
		else if (b[0][2] == 'O')
			return -10;
	}

	// Else if none of them have won return 0
#if defined (DEBUG)
	//printf("No one one\n");
#endif
	return 0;
}

// This is the minimax function. It considers all
// the possible ways the game can go and returns
// the value of the board
int minimax(char board[3][3], int depth, bool isMax) {
	int score = evaluate(board);
#if	defined (DEBUG)
	printf("Board to be evaluated\n");
	showBoard(board);
#endif

	// If maximizer has won the game return his/her
	// evaluated score
	if (score == 10)
		return score - depth;		// - depth to win fastest
	
	// If minimizer has won the game return his/her 
	//evaluated score
	if (score == -10)
		return score + depth;		// + depth to prolong defeat

	// If there are no more moves and no winner then
	// it is a tie
	if (isMovesLeft(board) == false){
#if defined (DEBUG)
	printf("No moves left\n");
#endif
		return 0;
	}
		
	// If this is maximizer's move
	if (isMax) {

		int best = -1000;

		// Traverse all cells 
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				// Check if cell is empty
				if (board[i][j] == ' ') {
					// Make the move
					board[i][j] = player;

					// Call the minimax recursively and choose
					// the maximum value
					best = max(best, minimax(board, depth + 1, !isMax));
#if defined (DEBUG)
					showBoard(board);
#endif

					// Undo the move
					board[i][j] = ' ';
				}
			}
		}
#if defined (DEBUG)
	printf("Best = %d\n", best);
#endif
		return best;

	}

	// If this is minimizer's move
	else {
		int best = 1000;

		// Traverse all cells
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				// Check if cell is empty
				if (board[i][j] == ' ') {
					// Make the move
					board[i][j] = opponent;

					// Call minimax recursively and choose the minimum value
					best = min(best, minimax(board, depth + 1, !isMax));
#if defined (DEBUG)
					showBoard(board);
#endif					

					// Undo the move
					board[i][j] = ' ';
				}
			}
		}
#if defined (DEBUG)
	printf("Best = %d\n", best);
#endif
		return best;
	}
}

// This function returns  the best posssible move for the player
Move findBestMove(char board[3][3]) {
	int bestVal = -1000;
	Move bestMove = {-1, -1};

	// Traverse all cells, evaluate minimax function for
	// all empty cells. And return the cell with optimal
	// value.

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			// Check if the cell is empty
			if (board[i][j] == ' ') {
#if defined (DEBUG)
	printf("Before the move\n\n");
	showBoard(board);
#endif
				// Make the move
				board[i][j] = player;
#if defined (DEBUG)
	printf("After making the move\n\n");
	showBoard(board);
#endif

				// Compute the evaluation function for this move
				int moveVal = minimax(board, 0, false);
#if defined (DEBUG)
				printf("i = %d\n", i);
				printf("j = %d\n", j);
				printf("bestVal = %d\n", bestVal);
				printf("moveVal = %d\n\n", moveVal);
#endif
				// Undo the move
				board[i][j] = ' ';
#if defined (DEBUG)
	printf("After undoing the move\n\n");
	showBoard(board);
#endif

				// If the value of the current move is
				// more than the best value, then update
				// bestVal and bestMove
				if (moveVal > bestVal) {
					bestMove.row = i;
					bestMove.col = j;
					bestVal = moveVal;
				}
			}
		}
	}
	printf("The value of the best Move is : %d\n\n", bestVal);

	return bestMove;
}

// Driver code

int main() {
	char board[3][3] = 
	{
		{'X', 'O', 'X'},
		{'O', 'O', 'X'},
		{' ', ' ', ' '}
	};

	Move bestMove = findBestMove(board);

	printf("The Optimal Move is : \n");
	printf("ROW: %d	COL: %d\n\n", bestMove.row, bestMove.col);

	return 0;
}
			
