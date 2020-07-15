#include "WinCon.h"


//////////////////////////////////////////Default Constructor ///////////////////////////////////////////
WinCon::WinCon()
{
	SCREEN_WIDTH = 120; //Screen Width Variable Initialized
	SCREEN_HEIGHT = 40; //Screen Width Variable Initialized

	HANDLE_CONSOLE_OUT = GetStdHandle(STD_OUTPUT_HANDLE); //Output Handle to the Console by Get Command 
	
	//MEMSET is used to initialize the keys struct and Input Arrays(Newer and Older) to get rid of garbage value.
	//(CODE TAKEN FROM THE INTERNET)
	memset(KEY_NEW_STATE, 0, 256 * sizeof(short));
	memset(KEY_OLD_STATE, 0, 256 * sizeof(short));
	memset(KEYS, 0, 256 * sizeof(STATE_OF_KEY));
}




//////////////////////////////////////////////Destructor /////////////////////////////////////////////
//To Set Back the ORIGINAL CONSOLE and Deallocate the SCREEN_BUFFER
WinCon::~WinCon()
{
	SetConsoleActiveScreenBuffer(ORGINAL_CONSOLE);
	delete[] SCREEN_BUFFER;
}




////////////////////////Constructing the Console Window with Height and Width as Parameters ////////////////////////
int WinCon::CONSTRUCT_THE_CONSOLE(int width, int height)
{
	
	//Size of the Console 
	SCREEN_WIDTH = width; 
	SCREEN_HEIGHT = height;
	
	//Set up the RECTANGLE( 2D coordinates) Canvas and passing it as CONSOLE WINDOW INFO. 
	RECT_WIN = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(HANDLE_CONSOLE_OUT, TRUE, &RECT_WIN);

	// SIZE OF THE SCREEN BUFFER
	//USING COORD (coordinates) ASSUMING THE CANVAS IS A 2D.
	COORD coord = { (short)SCREEN_WIDTH, (short)SCREEN_HEIGHT };

	// PHYSICAL WINDOW SIZE (THE APPEARANCE)
	RECT_WIN = { 0, 0, (short)SCREEN_WIDTH - 1, (short)SCREEN_HEIGHT - 1 };

	// ALLOCATING MEMORY TO THE SCREEN BUFFER of type ( CHAR_INFO ). IT'S A 16 BIT UNICODE.
	SCREEN_BUFFER = new CHAR_INFO[SCREEN_WIDTH * SCREEN_HEIGHT];

	//Initializing the CHAR_INTO STRUCT with memset to 0
	memset(SCREEN_BUFFER, 0, sizeof(CHAR_INFO) * SCREEN_WIDTH * SCREEN_HEIGHT);

	return 1;
}




/////////////////////DRAWING THE BORDERS of the game (Only for the Aesthetic purposes)///////////////////////////////////////
void WinCon::DRAW_BORDERS()
{
	//LEFT Side Borders 
	for (int i = 0; i < SCR_HEIGHT() - 1; i++)
	{
		SCREEN_BUFFER[i * SCR_WIDTH() + 1].Char.UnicodeChar = L'\u2551';
	}
	//RIGHT Side Borders 
	for (int i = 2; i < SCR_HEIGHT(); i++)
	{
		SCREEN_BUFFER[i * SCR_WIDTH() - 1].Char.UnicodeChar = L'\u2551';
	}
	//UP, DOWN, and CORNERS 
	for (int i = 1; i < SCR_WIDTH() * SCR_HEIGHT(); i++)
	{
		if (i == 1)
			SCREEN_BUFFER[i].Char.UnicodeChar = L'\u2554';
		else if (i < SCR_WIDTH() - 1 && i > 1)
			SCREEN_BUFFER[i].Char.UnicodeChar = L'\u2550';
		else if (i == SCR_WIDTH() - 1)
			SCREEN_BUFFER[i].Char.UnicodeChar = L'\u2557';
		else if (i == (SCR_WIDTH() * (SCR_HEIGHT() - 1)) + 1)
			SCREEN_BUFFER[i].Char.UnicodeChar = L'\u255A';
		else if (i <= ((SCR_WIDTH() * SCR_HEIGHT()) - 2) && i > ((SCR_WIDTH() * (SCR_HEIGHT() - 1)) + 1))
			SCREEN_BUFFER[i].Char.UnicodeChar = L'\u2550';
		else if (i == ((SCR_WIDTH() * SCR_HEIGHT()) - 1))
			SCREEN_BUFFER[i].Char.UnicodeChar = L'\u255D';
		continue;
	}
}




///////////////////////DRAWING OF THE PADDLE (one of the important object of the Game)////////////////////////////
void WinCon::DRAW_PADDLE(int& Y, bool RIGHT)
{
	if (RIGHT == false) 
	{
		//Player 1
		for (int J = Y; J <= Y + 7; J++) {
			for (int I = (SCR_WIDTH() * J) + 4; I <= ((SCR_WIDTH() * J) + 5); I++) SCREEN_BUFFER[I].Char.UnicodeChar = L'\u2588';
		}
	}
	else {
		//Player 2
		for (int Z = Y; Z <= Y + 7; Z++)
		{
			for (int I = (SCR_WIDTH() * Z) - 4; I >= ((SCR_WIDTH() * Z) - 5); I--) SCREEN_BUFFER[I].Char.UnicodeChar = L'\u2588';
		}
	}
}




////////////////////Drawing the Separation Line to differentiate the Playground of the two players///////////////////////
void WinCon::DRAW_SEPARATION_LINE()
{
	for (int i = 4; i < SCR_HEIGHT() - 1; i += 2)
	{
		SCREEN_BUFFER[i * SCR_WIDTH() + 60].Char.UnicodeChar = L'\u2502'; //VERTICAL LINE
	}
}




////////////DRAW STRING FUNCTION taken from the INTERNET. As it is a Unicode we have a posibility of COLOR as well.//////////////
void WinCon::DRAW_STRING(int X, int Y, wstring STRING, short COLOR)
{
	for (size_t i = 0; i < STRING.size(); i++)
	{
		SCREEN_BUFFER[Y * SCREEN_WIDTH + X + i].Char.UnicodeChar = STRING[i];
		SCREEN_BUFFER[Y * SCREEN_WIDTH + X + i].Attributes = COLOR;
	}
}




/////////////////////////////////////////////////DRAW BALL/////////////////////////////////////////////////
void WinCon::DRAW_BALL(float& x, float& y)
{
	int j = (int)y;
	for(int i = (int)x-1;i<=x;i++)
	{
		SCREEN_BUFFER[j * SCREEN_WIDTH + i].Char.UnicodeChar = L'\u2588';
	}
}




/////////////////////////////////////////////////////CLEAR THE SCREEN/////////////////////////////////////////
void WinCon::CLEAR_SCREEN()
{
	for (int i = 0; i <= SCR_WIDTH() * SCR_HEIGHT(); i++) 
	{
		SCREEN_BUFFER[i].Char.UnicodeChar = L' ';
		SCREEN_BUFFER[i].Attributes = FOREGROUND_WHITE;
	}
}




///////////////////////////////////////UPDATING THE SCORE//////////////////////////////////////////////////
void WinCon::SCORE_UPDATE(int SCORE_P1, int SCORE_P2)
{
	DRAW_STRING(16, 2, L"Player 1: " + to_wstring(SCORE_P1));
	DRAW_STRING(56, 2, L"<-SCORE->");
	DRAW_STRING(92, 2, L"Player 2:  " + to_wstring(SCORE_P2));
}




////////////////////////////////////DECIDES WHO WINS AND WRITES TO THE FILE/////////////////////////////////
void WinCon::WHO_WINS(int P1_SCORE,int P2_SCORE)
{
	if ((P1_SCORE == 5) || (P2_SCORE == 5))
	{
		//////////////////////////////WRITING INTO THE FILE/////////////////////////////////
		fstream WRITE;
		WRITE.open("Game_Data.txt", ios::app);//ONLY INPUT
		{
			if (P1_SCORE > P2_SCORE)
				WRITE << endl << "\t" << "WINNER is P1";
			else
				WRITE << endl << "\t" << "WINNER is P2";
		}
		WRITE.close(); 
	}
	else
	{
		DRAW_SEPARATION_LINE();
	}
}



/////////////////////////////////////////////START FUNCTION///////////////////////////////////
void WinCon::START()
{
	ACTIVE = true;

	// STARTING THE THREAD
	thread T = thread(&WinCon::GAME_THREAD, this);

	// WAIT FOR THE THREAD TO EXIT
	T.join();
}



///////////////////////////GET SCREEN WIDTH///////////////////////////////////////
int WinCon::SCR_WIDTH()
{
	return SCREEN_WIDTH;
}



////////////////////////////////GET SCREEN HEIGHT///////////////////////////////
int WinCon::SCR_HEIGHT()
{
	return SCREEN_HEIGHT;
}




///////////////////////////////////////GAME THREAD FUNCTION//////////////////////////////////////
void WinCon::GAME_THREAD()
{
	// Create user resources as part of this thread
	if (!PREPARE())
		ACTIVE = false;
	auto TIME_POINT1 = chrono::system_clock::now();
	auto TIME_POINT2 = chrono::system_clock::now();

	while (ACTIVE)
	{
		///////////////////// Run as fast as possible/////////////
		while (ACTIVE){
		

			////////////////////////////////////TIMING (USING CHRONO LIBRARY)//////////////////////////////////
			//To get the ----> 1/Frame-Rate
			TIME_POINT2 = chrono::system_clock::now();
			chrono::duration<float> TIME_PASSED = TIME_POINT2 - TIME_POINT1;
			TIME_POINT1 = TIME_POINT2;
			float TIME_FRAME = TIME_PASSED.count();



			/////////////////////////KeyBoard Input (Borrowed Code from internet)///////////////////////////////
			for (int i = 0; i < 256; i++)
			{
				KEY_NEW_STATE[i] = GetAsyncKeyState(i);

				KEYS[i].Pressed = false;

				if (KEY_NEW_STATE[i] != KEY_OLD_STATE[i])
				{
					if (KEY_NEW_STATE[i] & 0x8000)
					{
						KEYS[i].Pressed = !KEYS[i].Held;
						KEYS[i].Held = true;
					}
					else
					{
						KEYS[i].Held = false;
					}
				}

				KEY_OLD_STATE[i] = KEY_NEW_STATE[i];
			}



			/////////////////////////////////// Handle Frame(DRAWING Update)////////////////////////////////////////
			if (!UPDATES(TIME_FRAME))
				ACTIVE = false;



			/////////////////////// Update Title & Present Screen Buffer///////////////////////////////////////////
			SetConsoleTitle(L"PONG");//Game Name

			HWND console = GetConsoleWindow(); //GET THE HANDLE type HWND

			//Set the toggle to not be able to MAXIMIZE the CONSOLE WINDOW
			SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

			//SET THE WINDOW in LEFT-HAND corner of the MONITOR
			MoveWindow(console, 100, 0, 1000,690, TRUE);

			//WRITE TO THE CONSOLE (EVERYTHING DONE SO FAR)
			WriteConsoleOutput(HANDLE_CONSOLE_OUT, SCREEN_BUFFER, { (short)SCREEN_WIDTH, (short)SCREEN_HEIGHT }, { 0,0 }, &RECT_WIN);
		}

		//////////////////////////////Optional Function////////////////////////////////////
		if (DESTROY_ME_PLEASE())
		{
			// User has permitted destroy, so exit and clean up
			delete[] SCREEN_BUFFER;
			SetConsoleActiveScreenBuffer(ORGINAL_CONSOLE);
		}
		else
		{
			///////////////////CONTINUE RUNNING/////////////////////////////
			ACTIVE = true;
		}
	}
	delete[] SCREEN_BUFFER;

	//Closing the Game Handle
	CloseHandle(HANDLE_CONSOLE_OUT);
}


//////////OPTIONAL FUNCTION for Clean Up of any Dynamic Memory Allocated.//////////////////////////////
bool WinCon::DESTROY_ME_PLEASE()
{
	return true;
}
