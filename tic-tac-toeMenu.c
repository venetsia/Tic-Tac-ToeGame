#include <stdio.h>
#include "tic-tac-toe.c"
#include "sinlgePlayerVsAI.c"

int choice;
int SinglePlayerMenu();

int main()
{ 
	do
	{
	 printf("\nMenu\n\n");
	 printf("1. Multiple Player\n");
	 printf("2. Single Player vs AI\n");
	 printf("3. Replay Multiple player game\n");
	 printf("4. Exit\n");
	 scanf("%d",&choice);
	   
		switch (choice)
		{
			case 1: MultiplePlayer();
				break;
			case 2: SinglePlayerMenu();
				break;
			case 3: ReplayMulti();
				break;
			case 4: exit(0);
				break;
			default: printf("Wrong Choice. Enter again\n");
				break;
		} 
	  
	} while (choice != 4);
}

int SinglePlayerMenu()
{
	int choice1;
	do
	{
		printf("\nMenu\n\n");
		printf("1. Easy\n");
		printf("2. Unbeatable\n");
		printf("3. Back\n");
		scanf("%d",&choice1);
		   
		switch (choice1)
		{
			case 1: SinglePlayer(choice1);
			    break;
			case 2: SinglePlayer(choice1);
				break;
			case 3: main();
				break;
			default: printf("Wrong Choice. Enter again\n");
				break;
		} 
	  
	} while (choice1 != 4);
	
	return 3;
}

