#include <stdio.h>		/*	printf, NULL	*/
#include <stdlib.h>		/* 	srand, rand 	*/
#include <time.h>		/*	time 			*/
using namespace std;

#define DEBUG
#undef DEBUG
#define WHOSE_TURN
#undef WHOSE_TURN


#define COMPUTER 1
#define HUMAN 2

#define SIDE 3		// Length of the board

// Computer will move with 'O'
// and human will move with 'X'
#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

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

// A function to show the instrcutions
void showInstructions() {
	printf("\t\t\t Tic-Tac-Toe\n\n");
	printf("Choose a cell numbered from 1 to 9 as below and play\n\n");
	printf("\t\t\t 1 | 2 | 3 \n");
	printf("\t\t\t-----------\n");
	printf("\t\t\t 4 | 5 | 6 \n");
	printf("\t\t\t-----------\n");
	printf("\t\t\t 7 | 8 | 9 \n");
	
	printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");

	return;
}


bool contains(int moves[], int moveIndex) {
	for (int i = 0; i < SIDE * SIDE; ++i) {
		if (moves[i] == moveIndex)
			return true;
	}
	return false;
}


void random_shuffle(int moves[]) {
	for (int i = 0; i < SIDE * SIDE; ++i ) {
		moves[i] = -1;
	}
	srand(time(NULL));
	
	for (int i = 0; i < SIDE * SIDE; ++i) {
		if (moves[i] == -1) {
			int moveIndex = rand() % (SIDE * SIDE);

			while (contains(moves, moveIndex)) {
				moveIndex = rand() % (SIDE * SIDE);
			}

			moves[i] = moveIndex;
		}
	}
}

			


// A function to initialize the game.
void initialize(char board[][SIDE], int moves[]) {
	// Initialize the random number generator so that 
	// the same configuaration doesn't arises
	srand(time(NULL));

	// Initially the board is empty
	for(int i = 0; i < SIDE; ++i) {
		for(int j = 0; j < SIDE; ++j) {
			board[i][j] = ' ';
		}
	}

	// Fill the moves with numbers
	for(int i = 0; i < SIDE * SIDE; ++i)
		moves[i] = i;
	
	// Randomize the moves
	random_shuffle(moves);

#if defined DEBUG
	printf("moves = ");
	for (int i = 0; i < SIDE * SIDE; ++i){
		printf("%d ", moves[i]);
	}
	printf("\n");
#endif

	return;
}

// A function to declare the winner of the game
void declareWinner(int whoseTurn) {
	if (whoseTurn == COMPUTER) 
		printf("COMPUTER has won\n");
	else
		printf("HUMAN has won\n");
	return;
}

// A function that returns true if any of the row
// is crossed with the same player's move

bool rowCrossed(char board[][SIDE]) {
	for (int i = 0; i < SIDE; ++i) {
		if (board[i][0] == board[i][1] &&
			board[i][1] == board[i][2] &&
			board[i][0] != ' ')
			return true;
	}
	return false;
}

// A function that returns true if any of the column
// is crossed with the same player's move
bool columnCrossed(char board[][SIDE]) {
	for(int i = 0; i < SIDE; ++i) {
		if (board[0][i] == board[1][i] &&
			board[1][i] == board[2][i] &&
			board[0][i] != ' ')
			return true;
	}
	return false;
}

bool diagonalCrossed(char board[][SIDE]) {
	if (board[0][0] == board[1][1] && 
		board[1][1] == board[2][2] &&
		board[0][0] != ' ')
		return true;
	if (board[0][2] == board[1][1] && 
		board[1][1] == board[2][0] &&
		board[0][2] != ' ')
		return true;

	return false;
}

// A function that returns true if the game is over
// esle it return false
bool gameOver(char board[][SIDE]) {
	return (rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board));
}

// A function to play Tic-Tac-Toe
void playTicTacToe(int whoseTurn) {
	// A 3 * 3 Tic-Tac-Toe board for playing
	char board[SIDE][SIDE];

	int moves[SIDE * SIDE];

	// Initialize the game
	initialize(board, moves);

	// Show the instructions before playing
	showInstructions();

	int moveIndex = 0, x, y;

#if defined (DEBUG)
	showBoard(board);
#endif

#if defined (DEBUG)
	if (gameOver(board))
		printf("Game over = true\n\n");
	else
		printf("Game over = false\n\n");
#endif

#if defined (DEBUG)
	if (rowCrossed(board))
         printf("Row Crossed = true\n\n");
     else
         printf("Row Crossed = false\n\n");
#endif
#if defined (DEBUG)
	if (columnCrossed(board))
         printf("Column Crossed = true\n\n");
     else
         printf("Column Crossed = false\n\n");
#endif
#if defined (DEBUG)
	if (diagonalCrossed(board))
         printf("Diagonal Crossed = true\n\n");
     else
         printf("Diagonal Crossed = false\n\n");
#endif
	// Keep playing until the game is over os it is a draw
	while (gameOver(board) == false &&
		   moveIndex != SIDE * SIDE) {
#if defined(DEBUG)
		printf("Entered while loop\n\n");
#endif
		if (whoseTurn == COMPUTER) {
			x = moves[moveIndex] / SIDE;
			y = moves[moveIndex] % SIDE;
			board[x][y] = COMPUTERMOVE;
			printf("COMPUTER has put a %c in cell %d\n", 
					COMPUTERMOVE, moves[moveIndex] + 1);
			showBoard(board);
			moveIndex++;
			whoseTurn = HUMAN;
		} else if (whoseTurn == HUMAN) {
			x = moves[moveIndex] / SIDE;
			y = moves[moveIndex] % SIDE;
			board[x][y] = HUMANMOVE;
			printf("HUMAN had put a %c in cell %d\n",
					HUMANMOVE	, moves[moveIndex] + 1);
			showBoard(board);
			moveIndex++;
			whoseTurn = COMPUTER;
		}
	}

	// If the game has drawn
	if (gameOver(board) == false &&
		moveIndex == SIDE * SIDE)
		printf("It's a draw\n");
	else {
		// Toggling the use to declare the actual winner
		
		if (whoseTurn == COMPUTER) {
#if defined (WHOSE_TURN)
			printf("Toggling from COMPUTER to HUMAN\n");
#endif
			whoseTurn = HUMAN;
		} else if (whoseTurn == HUMAN) {
#if defined (WHOSE_TURN)
			printf("toggling form HUMAN to COMPUTER\n");
#endif
			whoseTurn = COMPUTER;
		}
		
		// Declare the winner
		declareWinner(whoseTurn);
	}
	return;
}

// Driver program
int main() {
	// Let us play the game with the computer starting first
	playTicTacToe(COMPUTER);

	return 0;
}





