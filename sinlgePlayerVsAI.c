#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/*
int board[25] = {
   :,:,:,:,:              :, :, : ,:,:
   :,-,-,-,:      ->      :, 6, 7, 8,:  
   :,-,-,-,:      ->      :,11,12,13,:  
   :,-,-,-,:              :,16,17,18,:
   :,:,:,:,:              :, :, :, :,:
   
    0,  1, 2, 3,  4,
	5,  6, 7, 8,  9,
	10 ,11,12,13, 14,
	15, 16,17,18, 19,
	20, 21,22,23, 24
   }
*/

//Enumarate constants  -> better than just initializing constants
//        0           1       2     3
enum { NOUGHTS, CROSSES, BORDER, EMPTY };
enum { HUMANWIN, COMPWIN, DRAW };


//12-13 is one
//12-18 is six
//12-17 is five
//12-16 is four
//times by minus one -> opposite direction
const int Directions[4] = { 1, 5, 4, 6 };

const int ConvertTo25[9] = {
	6, 7, 8,
	11,12,13,
	16,17,18
};

const int InMiddle = 4;
const int Corners[4] = { 0, 2, 6, 8 };

int ply = 0;
int positions = 0;
int maxPly = 0;

//gets the starting square as an argument
//						17				5                          player
int GetNumForDir(int startSq, const int dir, const int *board, const int us) {
	int found = 0;
	//while we have not hit the border
	while(board[startSq] != BORDER)
	{	
		//the the square is not equal to the same mark
		if(board[startSq] != us)
		{	
			break;
		}
		//otherwise increment the score by one
		found++;
		//add the direction to the start square (if from 17 we add 5 it would go to 22 and it would break
		//because it is a border
		startSq += dir;
	}	
	return found;
}

//got out board; ourindex is the square that we are on the moment, and player(mark)
int FindThreeInARow(const int *board, const int ourindex, const int us) {

	int DirIndex = 0; //loop index
	int Dir = 0; //particular direction in the array
	int threeCount = 1; //how many marks in a row
	
	//do checks for all possible directions
	for(DirIndex = 0; DirIndex < 4; ++DirIndex) {
		Dir = Directions[DirIndex]; //gets Directions[4] = { 1, 5, 4, 6 };
		
		//find a mark on player in direction{1,5,4 or 6}, starting at our square + 1
		// going to direction 1
		//getting board 
		// and player mark
		threeCount += GetNumForDir(ourindex + Dir, Dir, board, us);
		
		//do exactly the same but multiply by -1 so we go to the opposite dirrection
		threeCount += GetNumForDir(ourindex + Dir * -1, Dir * -1, board, us);
		
		//if we get three we break and win
		if(threeCount == 3) {
			break;
		}
		//otherwise we set threeCount to one and loop in next direction
		threeCount = 1;
	}
	return threeCount;
}

int FindThreeInARowAllBoard(const int *board, const int us) {
	int threeFound = 0;
	int index;
	for(index = 0; index < 9; ++index) {
		if(board[ConvertTo25[index]] == us) {
			if(FindThreeInARow(board, ConvertTo25[index], us) == 3) {				
				threeFound = 1; 
				break;
			}
		}
	}	
	return threeFound;
}

int EvalForWin(const int *board, const int us) {

	if(FindThreeInARowAllBoard(board, us) != 0)
		return 1;
	if(FindThreeInARowAllBoard(board, us ^ 1) != 0)
		return -1;
	
	return 0;
}

int MinMax(int *board, int side) {

	// check is a win
	// gen all moves for side
	// loop moves, make move, mimax() on move to get score
	// assess bestscore
	// end moves return bestscore
	
	int MoveList[9];
	int MoveCount = 0;
	int bestScore = -2;
	int score = -2;
	int bestMove = -1;
	int Move;
	int index;
	
	if(ply > maxPly) maxPly = ply;	
	positions++;
	
	if(ply > 0) {
		score = EvalForWin(board, side);
		if(score != 0) {					
			return score;
		}		
	}
	
	// fill Move List
	for(index = 0; index < 9; ++index) {
		if( board[ConvertTo25[index]] == EMPTY) {
			MoveList[MoveCount++] = ConvertTo25[index];
		}
	}
	
	// loop all moves
	for(index = 0; index < MoveCount; ++index) {
		Move = MoveList[index];
		board[Move] = side;	
		
		ply++;
		score = -MinMax(board, side^1);
		if(score > bestScore) {			
			bestScore = score;	
			bestMove = Move;
		}
		board[Move] = EMPTY;
		ply--;
	}
	
	if(MoveCount==0) {
		bestScore = FindThreeInARowAllBoard(board, side);	
	}
	
	if(ply!=0)
		return bestScore;	
	else 
		return bestMove;	
}

//Get empty squares at middle
void InitialiseBoard(int *board) {
	int index = 0; //index for looping
	
	for(index = 0; index < 25; ++index) {
		board[index] = BORDER; //Get BORDER -> :
	}
	
	for(index = 0; index < 9; ++index) {
		board[ConvertTo25[index]] = EMPTY; //Get Empty squares -> -
	}	
}

void PrintBoard(const int *board) {
	int index = 0; //index for looping
	
	//Get O and X and - for board
	char pceChars[] = "OX|-";	
	
	printf("\n\nBoard:\n\n");
	
	//Print proper board
	for(index = 0; index < 9; ++index) 
	{
		//in the end of every 3 squares  print line
		if(index!=0 && index%3==0) 
		{ 
			printf("\n\n");
		}
		// with four characters print board
		printf("%4c",pceChars[board[ConvertTo25[index]]]); //convert to 25 for our 9 base format
	}
	printf("\n");
}

int HasEmpty(const int *board) 
{
	int index = 0; // index for loop
	
	//loop through our nine squares
	for(index = 0; index < 9; ++index) 
	{
		// if we come across a square that is empty
		if( board[ConvertTo25[index]] == EMPTY) 
			return 1; // because we found an empty square
	}
	return 0;
}

//get a pointer to our board, the square that is the move made and the player
void MakeMove(int *board, const int sq, const side) 
{
	//board at square is equal to player ( x or o)
	board[sq] = side;
}

int GetNextBest(const int *board) {

	int ourMove = ConvertTo25[InMiddle];
	if(board[ourMove] == EMPTY) {
		return ourMove;
	}
	
	int index = 0;
	ourMove = -1;
	
	for(index = 0; index < 4; index++) {
		ourMove = ConvertTo25[Corners[index]];
		if(board[ourMove] == EMPTY) {
			break;
		}
		ourMove = -1;
	}
	
	return ourMove;
}

int GetWinningMove(int *board, const int side) {

	int ourMove = -1;
	int winFound = 0;
	int index = 0;
	
	for(index = 0; index < 9; ++index) {
		if( board[ConvertTo25[index]] == EMPTY) {
			ourMove = ConvertTo25[index];
			board[ourMove] = side;
			
			if(FindThreeInARow(board, ourMove, side) == 3) {
				winFound = 1;
			}	
			board[ourMove] = EMPTY;
			if(winFound == 1) {
				break;
			}
			ourMove = -1;
		};
	} 
	return ourMove;
}

//pointer to board and computer side
int GetComputerMove(int *board, const int side) {
	
	ply=0;
	positions=0;
	maxPly=0;
	int best = MinMax(board, side);
	printf("Finished Searching positions:%d maxDepth:%d bestMove:%d\n",positions,maxPly,best);
	return best;
	
}

int GetComputerMoveEASY(const int *board) 
{
	int index = 0;
	int numFree = 0;
	int availableMoves[9];
	int randMove = 0;	
	/* 2,4,8
		availableMoves[0] = 2 numFree++ -> 1;
		availableMoves[numFree] = 4 numFree++ -> 2;
		availableMoves[numFree] = 8 numFree++ -> 3
		
		rand() % numFree gives 0 to 2
		
		rand from 0 to 2, return availableMoves[rand]
	*/
	//Loop through board
	for(index = 0; index < 9; ++index) 
	{
		//If square empty
		if( board[ConvertTo25[index]] == EMPTY) 
		{
			//Assign square to available move
			availableMoves[numFree++] = ConvertTo25[index];	//postincrementing
				//numFree++ --> first use numFree and then increment it
				//++numFree --> first increment and then use numFree
		};
	}
	
	//get random move
	randMove = (rand() % numFree);
	//get move from one of the available move
	return availableMoves[randMove];
}

int GetHumanMove(const int *board) 
{
	//move characters is 2 characters
	char userInput[4];
	
	int moveOk = 0;
	int move = -1;
	
	while (moveOk == 0) 
	{
	
		printf("Please enter a move from 1 to 9:");		
		fgets(userInput, 3, stdin); //take 3 characters
		//fflush gets rid of crappy  inputs like -> fjakfjalfja6
		//if not for fflush, program would take 3 characters fail and until the end until we have 6 and make a move
		fflush(stdin);
		
		// a number and an enter is 2 so if not print error
		if(strlen(userInput) != 2) 
		{
			printf("Invalid strlen()\n");
			continue;			
		}
		
		//use sscanf to format our string (if for date %d/%d/%d)
		//we have one number to pass
		if( sscanf(userInput, "%d", &move) != 1) 
		{
			//if not valid make move to nothing (nothing stored just in case
			move = -1;
			printf("Invalid sscanf()\n");
			continue;
		}
		
		//test if move is in range
		if( move < 1 || move > 9) {
			move = -1;
			printf("Invalid range\n");
			continue;
		}
		
		move--; // Zero indexing
		
		//Check if square is free to move on to
		if( board[ConvertTo25[move]]!=EMPTY)
		{
			//if not valid make move to nothing (nothing stored just in case
			move=-1;
			printf("Square not available\n");
			continue;
		}
		//if move okey make moveOK=1 and end while loop
		moveOk = 1;
	}
	//print move made by human
	printf("Making Move...%d\n",(move+1));
	return ConvertTo25[move];
}

void RunGame() {

	int GameOver = 0; //If game over it would be 1
	int Side = CROSSES; // the computer would be first
	int LastMoveMade = 0; 
	int board[25];
	
	InitialiseBoard(&board[0]);
	PrintBoard(&board[0]);
	
	//if game over is one the game is going to run
	while(!GameOver) 
	{
		//Human
		if(Side==NOUGHTS)
		{	
			//get move from human, make move on board, change side;
			LastMoveMade = GetHumanMove(&board[0]);
			MakeMove(&board[0],LastMoveMade,Side);
			Side=CROSSES; 
		} else 
		{
			//get move from computer, make move on board, change side;
			LastMoveMade = GetComputerMove(&board[0], Side);
			MakeMove(&board[0],LastMoveMade,Side);
			Side=NOUGHTS;
			PrintBoard(&board[0]);
		}
		
		// if three in a row exists Game is over
		//find the in a row (in board, take the last move made(ourindex), change the side) == 3
		if( FindThreeInARow(board, LastMoveMade, Side ^ 1) == 3) 
		{
			printf("Game over!\n");
			GameOver = 1;
			//we know the computer the computer won because he was crosses on LastMoveMade before changing side
			if(Side==NOUGHTS)
			{
				printf("Computer Wins\n");
			} 
			else 
			{
				printf("Human Wins\n");
			}
		}	
		
		// if no more moves, game is a draw	
		if(!HasEmpty(board)) {
			printf("Game over!\n");
			GameOver = 1;
			printf("It's a draw\n");
		}
	}
	
	//print a cross on square 1
	PrintBoard(&board[0]);
}
void RunGameEasy() 
{

	int GameOver = 0; //If game over it would be 1
	int Side = NOUGHTS; // the computer would be first
	int LastMoveMade = 0; 
	int board[25];
	
	InitialiseBoard(&board[0]);
	PrintBoard(&board[0]);
	
	//if game over is one the game is going to run
	while(!GameOver) 
	{
		//Human
		if(Side==NOUGHTS)
		{	
			//get move from human, make move on board, change side;
			LastMoveMade = GetHumanMove(&board[0]);
			MakeMove(&board[0],LastMoveMade,Side);
			Side=CROSSES; 
		} 
		else 
		{
			//get move from computer, make move on board, change side;
			LastMoveMade = GetComputerMoveEASY(&board[0]);
			MakeMove(&board[0],LastMoveMade,Side);
			Side=NOUGHTS;
			PrintBoard(&board[0]);
		}
		
		// if three in a row exists Game is over
		//find the in a row (in board, take the last move made(ourindex), change the side) == 3
		if( FindThreeInARow(board, LastMoveMade, Side ^ 1) == 3) 
		{
			printf("Game over!\n");
			GameOver = 1;
			//we know the computer the computer won because he was crosses on LastMoveMade before changing side
			if(Side==NOUGHTS)
			{
				printf("Computer Wins\n");
			} 
			else 
			{
				printf("Human Wins\n");
			}
		}	
		
		// if no more moves, game is a draw	
		if(!HasEmpty(board)) {
			printf("Game over!\n");
			GameOver = 1;
			printf("It's a draw\n");
		}
	}
	
	//print a cross on square 1
	PrintBoard(&board[0]);
}

int SinglePlayer(int choice1) 
{
	if(choice1 == 1)
	{
		//Random number generator
		srand(time(NULL));
		RunGameEasy();
		
	}
	else if(choice1 == 2)
	{
		//Random number generator
		srand(time(NULL));
		RunGame();
	}
	
		
	return 0;
}