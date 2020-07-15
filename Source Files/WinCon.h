#pragma once

#include "Ball.h"
#include "Paddle.h"


#include <iostream>// Input-Output Standard Library 
#include <chrono>//Library for taking out the time points to get the Frame Rate.
#include <thread> //Library for Thread Function
#include <sstream> // WSTRING and many more on BUFFER.
#include <fstream>// Library for writing into and reading from a file.

using namespace std;

#include <windows.h> // Windows Library for Windows commands (therefore it's platform dependent). This won't work on Linux and MAC OS.


#define FOREGROUND_YELLOW 0x000E
#define	FOREGROUND_WHITE 0x000F


/////////////////////////////CONSOLE Window CLASS/////////////////////////////////
//ABSTRACT CLASS
class WinCon
{
public:
	WinCon(); // default Constructor
	~WinCon();// destructer

public:
	// How big of the CANVAS to draw (by default: it's 120*40 characters)-> We shouldn't change the value as it is optimized for PONG GAME.
	int CONSTRUCT_THE_CONSOLE(int width, int height); 
	void START();// Marks the START of the Game( it has to be called to create GAME WINDOW

public:
	void DRAW_PADDLE(int& Y, bool RIGHT); // Drawing the paddles
	void DRAW_STRING(int X, int Y, wstring STRING, short COLOR = FOREGROUND_YELLOW);// Writing on the buffer Console
	void DRAW_BORDERS(); // Design Asthetic 
	void DRAW_SEPARATION_LINE(); // Line Separation the Playground of two players
	void DRAW_BALL(float& x, float& y);
	int SCR_WIDTH(); //get the ScreenWidth
	int SCR_HEIGHT(); //get the ScreenHeight
	void CLEAR_SCREEN(); // Clears the Screen TIME_FRAME no. of times.
	void SCORE_UPDATE(int SCORE_P1, int SCORE_P2); // Score Gets updated unless One of them gets 5 Points
	void WHO_WINS(int P1_SCORE, int P2_SCORE); //Functiond decides who wins and writes to the File.

protected:

	void GAME_THREAD(); //Game thread Function


//////////////////////////////PURE VIRTUAL FUNCTIONS ///////////////////////////////////
	
	//These functions has to be Overided (Virtual)
	virtual bool PREPARE() = 0;// Some Basic Creation
	virtual bool UPDATES(float TIME_DIFFERENCE) = 0; //FREQUENTLY UPDATED

	////Cleans Up the Buffer(Dynamically Allocated Memory)-> No Memory Leak
	bool DESTROY_ME_PLEASE();

public:
	//Key States Struct (Code taken from the internet). To save which one is currently Pressed
	struct STATE_OF_KEY
	{
		bool Pressed;
		bool Held;
	} KEYS[256];

public:
	//Same Code about KEY struct taken from the Internet. Get the protected Key presses by this GetKey method.
	STATE_OF_KEY GetKey(int KEY_ID) { return KEYS[KEY_ID]; }

public:
	int BDX, BDY; // Direction Varaibles stored in here.
	float fNewY, fNewX; // Storing the BALL position (it's more easier to write)  
	int pos1, pos2; // Position iof the Paddles casted into INT.
	int SCREEN_WIDTH;//Buffer Weight Variable
	int SCREEN_HEIGHT; //Buffer Height Variable
	CHAR_INFO* SCREEN_BUFFER; // It's a Unicode based struct.
	HANDLE ORGINAL_CONSOLE; // Handle to the Console
	CONSOLE_SCREEN_BUFFER_INFO INFO_ORGINAL_CONSOLE; //Handle Info Stored into the Variable
	HANDLE HANDLE_CONSOLE_OUT; //Handle to the OUTPUT Console
	SMALL_RECT RECT_WIN; // Just for 2D coordinated buffer allocation
	short KEY_OLD_STATE[256] = { 0 }; //Previous Key Press
	short KEY_NEW_STATE[256] = { 0 };// This Newer keypress is compared to the previous one.
	bool ACTIVE; //Game Loop (Thread) Variable
};
