#include "Pong.h"
#include <fstream>

Pong::Pong() : WinCon(), Ball(), Paddle() //calling DEFAULT CONSTRUCTOR of inherited classes
{
	////////////////////////////// MEMORY MANAGEMENT ////////////////////////////////
	//Allocating Memory to OBJECT Pointers
	ball_obj = new Ball(60.0, 12.0, 60.0f);
	PLAYER1 = new Paddle(4.0, 16.0);
	PLAYER2 = new Paddle(116.0, 17.0);
} //Default Constructor

//Destructor
Pong::~Pong()
{
	//Objects get deleted when program ends.
	delete ball_obj, PLAYER1, PLAYER2;
}

////////////////////////////////////UPDATE to the Variables( drawn at newer position ) //////////////////////
bool Pong::UPDATES(float TIME_FRAME)
{
	if (GAME_RESET) //RESET THE GAME
	{
		GAME_OVER = false;
		GAME_RESET = false;
	}
	/////////////////////////GAME OVER////////////////////////////////////
	if (GAME_OVER)
	{
		DRAW_STRING(45, 20, L"Press ENTER to PLAY another GAME.", 0x000E);
		if (GetKey(VK_RETURN).Pressed) //START A NEW GAME after pressing ENTER
		{
			//Calling NEW GAME FUNCTION
			NEW_GAME();
			GAME_RESET = true;
		}
	}
	else
	{
		//////////CLEAR THE SCREEN////////////
		CLEAR_SCREEN();

		////////////DRAW_BORDERS/////////////
		DRAW_BORDERS();

		///////////////////////////////////////PADDLE MOVEMENT////////////////////////////////////////////

		//EXCEPTION HANDLING
		try
		{ //try block

			if (TIME_FRAME == 0)
				throw 0.0; //throw if the TIME_FRAME falls to zero (causing zero movement)

			//Player 1 SLIDES UP
			if (GetKey(0x57).Held)
			{
				if (PLAYER1->PLAYER_Y > 2)
					PLAYER1->PLAYER_Y -= 40.0f * TIME_FRAME;
			}
			//Player 1 SLIDES DOWN
			if (GetKey(0x53).Held)
			{
				if (PLAYER1->PLAYER_Y < SCR_HEIGHT() - 9)
					PLAYER1->PLAYER_Y += 40.0f * TIME_FRAME;
			}

			//Player 2 SLIDES UP
			if (GetKey(VK_UP).Held)
			{
				if (PLAYER2->PLAYER_Y > 3)
					PLAYER2->PLAYER_Y -= 40.0f * TIME_FRAME;
			}
			//Player 2 SLIDES DOWN
			if (GetKey(VK_DOWN).Held)
			{
				if (PLAYER2->PLAYER_Y < SCR_HEIGHT() - 8)
					PLAYER2->PLAYER_Y += 40.0f * TIME_FRAME;
			}
		}
		catch (float MSG) // catch it if exception thrown!!!
		{
			//Written on the Console buffer.
			DRAW_STRING(50, 30, L" The Frame Rate cannot be " + to_wstring(MSG));
		}

		//////////////////////////////////////  COLLISION LOGIC  ////////////////////////////////////////////

		float fOldX = ball_obj->BALL_X; //SAVE BALL OLD X
		float fOldY = ball_obj->BALL_Y; // SAVE BALL OLD Y

		//BALL CHNAGES POSITION
		float fNewX = ball_obj->BALL_X += BDX * TIME_FRAME * ball_obj->SPEED;
		float fNewY = ball_obj->BALL_Y += BDY * TIME_FRAME * ball_obj->SPEED;

		//old ball position casted front float to int
		int oldPOSX = (int)fOldX;
		int oldPOSY = (int)fOldY;

		//new ball position casted front float to int
		int newPOSX = (int)fNewX;
		int newPOSY = (int)fNewY;

		// Y POSITION OF BOTH THE PADDLES downcasted to int
		pos1 = (int)PLAYER1->PLAYER_Y;
		pos2 = (int)PLAYER2->PLAYER_Y;

		//EXCEPTION HANDLING
		try
		{ //try block
			if (BDX == 0 && BDY == 0)
				throw 0; //throw exception if Ball not moving

			//////////////////////////////PADDLE PLAYER 2////////////////////////////////////

			if (fOldX >= SCR_WIDTH() - 7 && newPOSX >= oldPOSX) //if ball reaches the right paddle
			{
				if (oldPOSY >= pos2 - 1 && oldPOSY <= pos2 + 2) //upper part of paddle
				{
					//CHANGE IN BALL DIRECTION
					if (fOldY <= -1)
					{
						BDX *= -1;
					}
					else
					{
						BDX *= -1;
						BDY *= -1;
					}
				}
				if (oldPOSY == pos2 + 3 || oldPOSY == pos2 + 4) //middle part of paddle
				{
					//CHANGE IN BALL DIRECTION
					BDX *= -1;
				}
				if (oldPOSY >= pos2 + 5 && oldPOSY <= pos2 + 7) //lower part of paddle
				{
					//CHANGE IN BALL DIRECTION
					if (fOldY <= -1)
					{
						BDX *= -1;
					}
					else
					{
						BDX *= -1;
						BDY *= -1;
					}
				}
			}

			//////////////////////////////PADDLE PLAYER 1////////////////////////////////////

			if ((fOldX <= (SCR_WIDTH() - (SCR_WIDTH() - 9)) && newPOSX <= oldPOSX)) //if ball reaches the LEFT paddle
			{
				if (oldPOSY >= pos1 && oldPOSY <= pos1 + 2) //upper part of paddle
				{
					//CHANGE IN BALL DIRECTION
					if (fOldY <= -1)
					{
						BDX *= -1;
					}
					else
					{
						BDX *= -1;
						BDY *= -1;
					}
				}
				if (oldPOSY == pos1 + 3 || oldPOSY == pos1 + 4) //middle part of paddle
				{
					//CHANGE IN BALL DIRECTION
					BDX *= -1;
				}
				if (oldPOSY >= pos1 + 5 && oldPOSY <= pos1 + 7) //lower part of paddle
				{
					//CHANGE IN BALL DIRECTION
					if (fOldY <= -1)
					{
						BDX *= -1;
					}
					else
					{
						BDX *= -1;
						BDY *= -1;
					}
				}
			}

			//////////////////////////COLLISION WITH LOWER WALL///////////////////////////
			if (oldPOSY >= SCR_HEIGHT() - 2 && newPOSY > oldPOSY)
			{
				//CHANGE IN BALL DIRECTION
				BDY *= -1;
			}
			//////////////////////////COLLISION WITH LOWER WALL///////////////////////////
			if (oldPOSY <= 2 && newPOSY < oldPOSY)
			{
				//CHANGE IN BALL DIRECTION
				BDY *= -1;
			}
		}
		catch (float NUM) //catch the exception if any
		{
			DRAW_STRING(50, 31, L" Ball has stopped -> X and Y are both " + to_wstring(NUM));
		}

		///////////////////////////////////////BALL Goes out of the Bound////////////////////////////

		//If goes to the left Side -> RESET + SCORE++
		if (fNewX < 2.000)
		{
			RESET();
			PLAYER2->SCORE++;
		}
		//If goes to the left Side -> RESET + SCORE++
		if (fNewX > SCR_WIDTH() - 2)
		{
			RESET();
			PLAYER1->SCORE++;
		}

		if (PLAYER1->SCORE == 5) //PLAYER1 WON
		{
			//SHOW ON SCREEN
			GAME_OVER = true;
			DRAW_STRING(54, 16, L"PLAYER 1 WON", 0x000E);
		}
		if (PLAYER2->SCORE == 5) //PLAYER2 WON
		{
			//SHOW ON SCREEN
			GAME_OVER = true;
			DRAW_STRING(54, 16, L"PLAYER 2 WON", 0x000E);
		}

		/////////////////////////////////////DRAWING THE SHAPES////////////////////////////////////////////////////////
		DRAW_PADDLE(pos1, false); //PLAYER1
		DRAW_PADDLE(pos2, true);  //PLAYER2
		DRAW_BALL(fNewX, fNewY);  //THE BALL

		/////////////////////////////////////////SCORE UPDATE//////////////////////////////////////////////////////////

		SCORE_UPDATE(PLAYER1->SCORE, PLAYER2->SCORE); //Scores of each individual gets Updated

		WHO_WINS(PLAYER1->SCORE, PLAYER2->SCORE); //Decide] the Winner
	}
	return true;
}



/////////////////////////////////////////////SET THE BALL WHEN IT GOES OUT OF THE BOUND ///////////////////////////
void Pong::RESET()
{
	ball_obj->BALL_X = ball_obj->INIT_X;
	ball_obj->BALL_Y = ball_obj->INIT_Y;
}



///////////////////////////////////////////START A NEW GAME AFTER PLAYING ONE OR MORE/////////////////////////////
void Pong::NEW_GAME()
{
	RESET();
	PLAYER2->PLAYER_Y = PLAYER2->DEFAULT_Y;
	PLAYER1->PLAYER_Y = PLAYER1->DEFAULT_Y;
	PLAYER1->SCORE = 0;
	PLAYER2->SCORE = 0;
}
