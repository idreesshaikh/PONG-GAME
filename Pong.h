#pragma once
#ifndef PONG_H
#define PONG_H

//Headers Added here
#include "Ball.h"
#include "Paddle.h"
#include "WinCon.h"

//Pong Class
//Child Class
class Pong :public WinCon, public Ball, public Paddle //Multiple Inheritance
{
public:
	//BOOL VARIABLES just to decide when to Finish the Game and when to Start a New One.
	bool GAME_OVER = false;
	bool GAME_RESET = true;

	//Pointer Objecte Variable
	Ball* ball_obj;
	Paddle* PLAYER1;
	Paddle* PLAYER2;
public:
	//Default Constructor
	Pong();

	//Destructor
	~Pong();

public:
	bool PREPARE()//To initialize some basic variables before the Game Starts.
	{

		BDX = ball_obj->BALL_DX;
		BDY = ball_obj->BALL_DY;
		return true; //Must return true to Carry on to the Game
	}

	bool UPDATES(float TIME_FRAME);//Objects' variables get updated and DRAWN to the Screen
	void RESET(); //Resets the ball wehn it gets out of the bound
	void NEW_GAME();//START a completely a NEW GAME
};
#endif
