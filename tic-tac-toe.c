#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define MAX 10
//Creating a Stack for undo option and redo option
struct stack
{
	int array[MAX];
	int top;
};

void init_stack(struct stack *);
void push(struct stack *, int item);
int *pop(struct stack *);

//Game board
char square[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

//initializing checkwin() function
int checkwin();
//initializing board() function
void board();

int MultiplePlayer()
{
	
	
    FILE *fp;//=fopen("test.txt", "w");
	      
    // test for files not existing. 
    

	struct stack undoTracker;
	struct stack redoTracker;
	init_stack(&undoTracker);
	init_stack(&redoTracker);
	
    int player = 1, i, choice;
	int stop = 1;
    char mark;
	
	char name[50];
	
	//Select a name for file that saves moves so we can do replay
	printf("Select a name for saving the game as replay: ");
	scanf("%s",name);
	//Open file (create new file)
	fp = fopen(name,"w");
	
	//If file is not open print error
	if (fp == NULL) 
    {   
        printf("Error! Could not open file\n"); 
        exit(-1); // must include stdlib.h 
    } 

    do
    {
		//Draw board
        board();
		//Two players
        player = (player % 2) ? 1 : 2;
		
		//Prompt Player for a move
        printf("Player %d, enter a number:  ", player);
        scanf("%d", &choice);

		//Mark the move for the player
        mark = (player == 1) ? 'X' : 'O';
		
		//If statements to check for choice and mark square
        if(choice == 1 && square[1] == '1') 
		{
			square[1] = mark;
			
		}
        else if (choice == 2 && square[2] == '2')
		{
            square[2] = mark;
			
		}
        else if (choice == 3 && square[3] == '3')
		{
            square[3] = mark;
			
		}
        else if (choice == 4 && square[4] == '4')
		{
            square[4] = mark;
			
		}
        else if (choice == 5 && square[5] == '5')
		{
            square[5] = mark;
			
		}
        else if (choice == 6 && square[6] == '6')
		{
            square[6] = mark;
		
		}
        else if (choice == 7 && square[7] == '7')
		{
            square[7] = mark;
			
		}
        else if (choice == 8 && square[8] == '8')
		{
            square[8] = mark;
			
		}
        else if (choice == 9 && square[9] == '9')
		{
            square[9] = mark;
			
		}
		else if (choice == 0)
		{
			stop = 0;
			break;   
		}
		else if(choice == 10) //Undo action if choice is 10
		{
			int *i = NULL;
			//Remove last item from stack, replacing the square with the number 
			i = pop(&undoTracker); 
			if(i)
			{
				
				square[*i] = *i+'0';
				printf("Undo move: %d\n", *i);
			}
			//Propt user for key insert for continue
			getch();
		}
        else //any other number would be invalid
        {
            printf("Invalid move ");

            player--;
            getch();
        }
        i = checkwin(); // check who wins

        player++; 
		if(choice != 10) //if choice is not undo, choice would be added to stack
		{
			//add to top of stack
			push(&undoTracker,choice);
			
		}
		fprintf(fp,"%d \n", choice); // write to file 
    }while (i ==  - 1);
    
	//Draw board 
    board();
    
    if (i == 1)
        printf("==>\aPlayer %d win ", --player);
	else if (stop == 0)
		printf("==>\aStopped Game\n");
    else
        printf("==>\aGame draw");
	
	//Clear the whole board so can start again
	do
	{
		int *i = NULL;
		i = pop(&undoTracker); //Remove last item from stack, replacing the square with the number 
		if(i)
		{
					
			square[*i] = *i+'0';
			
		}
	}while(isempty(&undoTracker) == 0);
	
	//Close file
	fclose(fp);
	//Prompt for user input to continue
    getch();

    return 0;
}

//// function to create a stack of given capacity. It initializes size of 
// stack as 0 
void init_stack(struct stack *s)
{
	s->top = -1;
}

//Returns top element of stack.
int peek(struct stack *s) {
   return s->top;
}

//Adds an item in the stack. If the stack is full, then it is said to be an Overflow condition
void push(struct stack *s, int item)
{
	if(s->top == MAX-1)
	{
		printf("Stack is full");
		return;
	}
	s->top++;
	s->array[s->top] = item;

}

//Removes an item from the stack. The items are popped in the reversed order in
//which they are pushed. If the stack is empty, then it is said to be an Underflow condition.
int *pop(struct stack *s)
{
	int *data;
	if(s->top == -1)
	{
		printf("Stack is empty\n");
		return NULL;
	}
	data = &s->array[s->top];
	s->top--;
	
	return data;
}
/*********************************************

FUNCTION TO RETURN GAME STATUS
1 FOR GAME IS OVER WITH RESULT
-1 FOR GAME IS IN PROGRESS
O GAME IS OVER AND NO RESULT
 **********************************************/
int checkwin()
{
    if (square[1] == square[2] && square[2] == square[3])
        return 1;
        
    else if (square[4] == square[5] && square[5] == square[6])
        return 1;
        
    else if (square[7] == square[8] && square[8] == square[9])
        return 1;
        
    else if (square[1] == square[4] && square[4] == square[7])
        return 1;
        
    else if (square[2] == square[5] && square[5] == square[8])
        return 1;
        
    else if (square[3] == square[6] && square[6] == square[9])
        return 1;
        
    else if (square[1] == square[5] && square[5] == square[9])
        return 1;
        
    else if (square[3] == square[5] && square[5] == square[7])
        return 1;
        
    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
        square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7] 
        != '7' && square[8] != '8' && square[9] != '9')

        return 0;
    else
        return  - 1;
}


/*******************************************************************
FUNCTION TO DRAW BOARD OF TIC TAC TOE WITH PLAYERS MARK
 ********************************************************************/


void board()
{
    system("cls");
    printf("\n\n\tTic Tac Toe\n\n");

    printf("Player 1 (X)  -  Player 2 (O)\n\n\n");

	printf("\nIf you want to stop game enter 0\n");

    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", square[1], square[2], square[3]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[4], square[5], square[6]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[7], square[8], square[9]);

    printf("     |     |     \n\n");
}

//Returns true if stack is empty, else false.
int isempty(struct stack *s)
{
    if (s->top==-1)
        return 1;
    else
        return 0;
}

//Function for replay moves in game
int ReplayMulti()
{
	char name[10];
	FILE *fp;
	printf("Enter file name for replay: ");
	scanf("%s", name);
	fp=fopen(name,"r");
	
		if (fp == NULL) 
		{   
			printf("Error! Could not open file\n"); 
			exit(-1); // must include stdlib.h 
		}		
	struct stack undoTracker;
	struct stack redoTracker;
	init_stack(&undoTracker);
	init_stack(&redoTracker);
	
    int player = 1, i, choice;
	int stop = 1;
    char mark;
	
	char nameF[50];
	if (fp == NULL ) 
    {   
        printf("Error! Could not open file\n"); 
        exit(-1); // must include stdlib.h 
    } 
	int c;
	
    do
    {

        board();
        player = (player % 2) ? 1 : 2;

        printf("Player %d, enter a number:  ", player);
        fscanf(fp,"%d", &choice); // get input from file each choice

        mark = (player == 1) ? 'X' : 'O';
		
        if(choice == 1 && square[1] == '1') // Checking that the square has not already been chosen
		{
			square[1] = mark;
			getch();
			
		}
        else if (choice == 2 && square[2] == '2')
		{
            square[2] = mark;
			getch();
			
		}
        else if (choice == 3 && square[3] == '3')
		{
            square[3] = mark;
			getch();
			
		}
        else if (choice == 4 && square[4] == '4')
		{
            square[4] = mark;
			getch();
			
		}
        else if (choice == 5 && square[5] == '5')
		{
            square[5] = mark;
			getch();
			
		}
        else if (choice == 6 && square[6] == '6')
		{
            square[6] = mark;
			getch();
		
		}
        else if (choice == 7 && square[7] == '7')
		{
            square[7] = mark;
			getch();
			
		}
        else if (choice == 8 && square[8] == '8')
		{
            square[8] = mark;
			getch();
			
		}
        else if (choice == 9 && square[9] == '9')
		{
            square[9] = mark;
			getch();
			
		}
		else if (choice == 0)
		{
			stop = 0;
			break;   
		}
		else if(choice == 10)
		{
			int *i = NULL;
			i = pop(&undoTracker); //Remove last item from stack, replacing the square with the number 
			if(i)
			{
				
				square[*i] = *i+'0';
				printf("Undo move: %d\n", *i);
			}
			
			getch();
		}
		
        i = checkwin();

        player++;
		if(choice != 10)
		{
			
			push(&undoTracker,choice);
			
		}
    }while ((c = fgetc(fp)) != EOF);
    
    board();
    
    if (i == 1)
        printf("==>\aPlayer %d win ", --player);
	else if (stop = 1)
		printf("==>\aStopped Game\n");
    else
        printf("==>\aGame draw");
	
	
	do
	{
		int *i = NULL;
		i = pop(&undoTracker); //Remove last item from stack, replacing the square with the number 
		if(i)
		{
					
			square[*i] = *i+'0';
			
		}
	}while(isempty(&undoTracker) == 0);
	
    getch();

    return 0;
	
}

/*******************************************************************
END OF PROJECT
 ********************************************************************/