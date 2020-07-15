#pragma once
#ifndef PADDLE_H
#define PADDLE_H

#include <iostream>

using namespace std;

//NO CPP FILE becasue it's just one constructor and Attributes/////

///////////////////////////////////////////Paddle Class////////////////////////////////////////////////


//Paddle Class
//(Parennt)
class Paddle
{
public://public becasue of the data Mondification 
	float PLAYER_X, PLAYER_Y; // Position of Paddles with their X and Y
	float DEFAULT_X, DEFAULT_Y; // Default Position
	int SCORE; //SCORE OF THE Player
public:
	//Multiple Parameter Constructor with Default Arguments
	Paddle(float XPOS = 0, float YPOS = 0)
	{
		DEFAULT_X = XPOS;
		DEFAULT_Y = YPOS;
		PLAYER_X = XPOS;
		PLAYER_Y = YPOS;
		SCORE = 0;
	}
};

#endif // !PADDLE_H
