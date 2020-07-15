#include <iostream>
#include <fstream>
#include "Pong.h"


//Please enable UNICODE (16 bit) CHARACTER SET. It has to enabled separately because unlike Extended ASCII(8 bit) it has far more braoder range.
#ifndef UNICODE
#error Please enable UNICODE for your compiler. 
#endif

///////////////////////////WRITING TO A FILE/////////////////////////////
//////////////File Handling( one the pre-requisite of the project)///////
void WRITE(string& P1, string& P2)
{
	fstream WRITE;
	WRITE.open("Game_Data.txt", ios::app);////GAME_DATA.txt file created if not already exist and later it is appeded
	{
		WRITE << "\nP1 = " << P1 << " vs " << " P2 = " << P2;
	}
	WRITE.close();//File Close
}


////////////////////////////////Game Menu/////////////////////////////////
	//VERY SIMPLE MENU TO nagivate to the GAME//

void MAIN_MENU()
{

	cout << "------------------------------------------------P O N G-----------------------------------------------\n" << endl;

	cout << endl << "\tEnter your Name to PLAY->  ";
	string PLAYER_1; //Taking input for Name of the PLayer 1.
	getline(cin, PLAYER_1);
	cout << "\n\t" << PLAYER_1 << " is Player 1!";

	cout << endl << "\tThe Controls for " << PLAYER_1 << " are 'W' to MOVE UP and 'S' to MOVE DOWN" << endl;//Outputing some basic instruction

	cout << endl << "\tEnter the Name to PLAY AGAINST with->  ";
	string PLAYER_2; //Taking input for Name of the PLayer 2.
	getline(cin, PLAYER_2);
	cout << "\n\t" << PLAYER_2 << " is Player 2!";
	cout << endl << "\tThe Controls for " << PLAYER_2 << " are 'UP ARROW' to MOVE UP and 'DOWN ARROW' to MOVE DOWN" << endl << endl;//Outputing some basic instruction

	cout << "\tWhosoever get 5 points first-> WINS " << endl << "\tPLayer 1 STARTS" << endl << endl; //GET 5 POINTS AND WIN THE GAME
	
	WRITE(PLAYER_1, PLAYER_2);
}

int main()
{
	MAIN_MENU();
	system("PAUSE"); //Waiting Gap between Game to be Started.

	//GAME STARTS
	Pong game;// Instantiated
	game.CONSTRUCT_THE_CONSOLE(120, 40); //Calling CONSTRUCT CONSOLE Function
	game.START(); // Calling START Function
	return 0; //Returns O if not error.
}