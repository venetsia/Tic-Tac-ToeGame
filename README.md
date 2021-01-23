# tic-tac-toe

## Tic-Tac-Toe game using C language usable on the command prompt
## Author: Venetsia Krasteva

### 1. Demo
* VS AI and Loading Project
![alt text](https://github.com/venetsia/Tic-Tac-ToeGame/blob/master/TicTacToeDemo.gif)
* VS Another Player (Multiplayer) and Reloading the game so you can watch (Replay)
![alt text](https://github.com/venetsia/Tic-Tac-ToeGame/blob/master/TicTacToeDemoMultipleP.gif)
	
### 1. Explaining how to use the Tic-Tac-Toe application
	* open Developer Command Prompt for Vs 2017 (DEV)
	* type nmake coursework
	* type tic-tac-toeMenu.exe
	* To delete all of the *.obj/ *.exe/ .*asm type nmake clean

### 2. A quick overview:
When you run the program you will have four opitons:
 1. Multiple Player 
 2. Single Player vs AI
 3. Replay Multiple player game 
 4. Exit
 
In Multiple player you firstly have to write a name for the file that will keep history of the movements in the game so it can replay them later. With choice 10 you undo the move you have made. Every other choice (from 1 to 9) is pushed into a stack so it can perform an Undo function. When someone wins the game ends and the board is cleared with a pop function from the stack.
In Single Player vs AI you would get another menu to choose from: 
1. Easy - *When you chose easy the game runs but the choices the computer makes are random.*
2. Unbeatable - *On unbeatable they are made with the MinMax algorithm to find the best next possible move of all so it runs all the options and finds the best one.*
3. Back -  *With choice Back you just go Back to the main menu.*

### Tool chain for building - Notepad++ v7.5.4 (32-bit)
### Running on: Visual Studio 2017 Tools Command Prompt (Developer Command Prompt for Vs 2017 (DEV))
