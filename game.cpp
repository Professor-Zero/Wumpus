/**
 *Game Class - This class has the user interface, and plays the game.
 */
//Mohamed Abdi
//CSS 342
//Cygwin
//10 hours

#include <stdlib.h>
#include "gameMap.h"
#include "room.h"
#include <iostream>

///////////////////
//Printing Methods
///////////////////

//prints out the instruction for the game.
void instructions() 
{
	cout << endl;
	cout << "Instructions: " << endl;
	cout << "The objective of the game is to kill the wumpus." << endl;
	cout << "You will have 4 arrows to kill the wumpus, but" << endl;
	cout << "there will be obstacles in the way that might kill you," << endl;
	cout << "and if you run out of arrows its game over." << endl;
	cout << endl;
}

//prints out the control keys for the game.
void controlKeys()
{
	cout << endl;
	cout << "Control keys: " << endl;
	cout << "To move use keys 'i' - up, 'l' - right, 'k' - down, 'j' - right" << endl;
	cout << "To shoot use key shift and keys 'i', 'l', 'k', or 'j' to aim" << endl;
	cout << "To cheat type \"map\"" << endl;
	cout << endl;

}
//prints what the user asks 
void printWhat(char userInput)
{
	switch(userInput) {
		case 's':
			cout <<"The game has began: "<< endl;
			break;
		case 'i':
			instructions();
			break;
		case 'c':
			controlKeys();
			break;
		default:
			cout << "wrong key. please try again." << endl;
	}
}
////////////////////////////////
//Game & user interaction Methods
////////////////////////////////

//This method gets the userinput and plays the game.
bool playGame(GameMap gM)
{
	while(gM.getGameStatus() == "")
	{
		cout << endl;
		cout << "what your player senses: " << endl;
		gM.detectRooms();
		string userInput;
		cout << endl;
		cout << "Type action and press enter: ";
		cin >> userInput;
		if(userInput == "i" || userInput == "j" || userInput == "k" || userInput == "l")
		{
			cout<<endl;
			char uI = userInput[0];
			gM.movePlayer(uI);
		}else if (userInput == "I" || userInput == "J" || userInput == "K" || userInput == "L")
		{
			cout << endl;
			char uI = userInput[0];
			gM.shootTheWumpus(uI);
		}else if(userInput == "map") 
		{
			gM.printMapAnswers();
		}else cout<<"wrong key input please try again!"<<endl;
	}
		cout << endl;
		cout << "Game status: " << gM.getGameStatus() << endl;
		cout << endl;	
}

///////////////////////
//Main method
////////////////////

int main()
{	
	bool playAgain = true;
	while(playAgain) 
	{
		string start = " ";
		while(start != "s")
		{
			cout << "Type 's' to start, 'i' for instruction, or 'c' for control keys: ";
			cin >> start;
			char start2 = start[0];
			printWhat(start2);
		}
		GameMap gM(8, 4, 4, 4); //size 8 by 8, 4 bats, 4 pits, and 4 shots to kill wumpus.
		gM.restartMap();
		//setting up wumpus game
		gM.setPlayerStart();
		playGame(gM);
		gM.clearMap();	
		//if user want to play again.
		string userAnswer = "";
		cout << "Do you want to play again(yes or no)? ";
		cin >> userAnswer;
		cout << endl;
		if(userAnswer != "yes") 
		{
			playAgain = false;	
		}
	}
	cin.get();
	return 0;
}
