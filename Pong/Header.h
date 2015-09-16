#pragma once
#include "sfwdraw.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

struct paddle
{
	float x1pos, y1pos, x2pos, y2pos;
	float yacc;
	float yvel;
	float yspeed;
	float score;
};

struct Ball
{
	float xpos, ypos;
	float xacc, yacc;
	float xvel, yvel;
	float speed;
};

bool paddleCollision(paddle playerPaddle, Ball projectile);