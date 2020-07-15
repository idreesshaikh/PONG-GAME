#pragma once
#ifndef BALL_H
#define BALL_H

#include <iostream>

using namespace std;

//NO CPP FILE becasue it's just one constructor and Attributes/////

///////////////////////////////////////////Ball Class////////////////////////////////////////////////
//(Parent) 
class Ball
{
public: //public becasue of the data Mondification 
	float BALL_X, BALL_Y; //Ball Position
	float INIT_X, INIT_Y; //Default Position
	int BALL_DX, BALL_DY; //Ball Directions
	float SPEED; //Speed of the Ball
public:
	//Multiple Parameter Constructor with Default Arguments
	Ball(float X_POS = 0.0, float Y_POS = 0.0, float SPEED= 60.0f) 
	{
		INIT_X = X_POS;
		INIT_Y = Y_POS;
		BALL_X = X_POS;
		BALL_Y = Y_POS;
		BALL_DX = -1, BALL_DY = -1;
		this->SPEED = SPEED;
	}
};
#endif // !BALL_H
