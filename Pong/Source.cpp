#include <iostream>
#include "sfwdraw.h"
#include "Header.h"
#include "drawRec.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void drawScore(float x, float y, float r, float score, float space)
{
	// initialize variables for drawing
	float drawX = x, drawY = y;

	for (int i = 0; i < score; i++)
	{
		// draw the circle
		sfw::drawCircle(drawX, drawY, r);

		// move the drawing cursor
		drawX += space + r;
	}
}

int main()
{
	sfw::initContext(SCREEN_WIDTH, SCREEN_HEIGHT, "Michael");

	paddle playerOne = {10, 250, 15, 350, 0, 0, 300, 0};
	paddle playerTwo = {785, 250, 790, 350, 0, 0, 300, 0};
	Ball projectile = {400, 300, 0, 0, 0, 0, 300};

	projectile.xvel = 0;
	projectile.yvel = 0;

	bool isRunning = true;

	while (sfw::stepContext() && isRunning)
	{
		//ball
		projectile.xpos += projectile.xvel * sfw::getDeltaTime();
		projectile.ypos += projectile.yvel * sfw::getDeltaTime();

		//left paddle
		playerOne.y1pos += playerOne.yvel * sfw::getDeltaTime();
		playerOne.y2pos = playerOne.y1pos + 100;

		//right paddle
		playerTwo.y1pos += playerTwo.yvel * sfw::getDeltaTime();
		playerTwo.y2pos = playerTwo.y1pos + 100;

		projectile.yacc = projectile.xacc = 0;
		if (sfw::getKey(32) && projectile.xvel == 0 && projectile.yvel == 0)
		{
			projectile.xvel = -400;
			projectile.yvel = -400;
		}
		playerOne.yacc = 0;
		if (sfw::getKey('w'))
		{
			playerOne.y1pos -= 350 * sfw::getDeltaTime();
		}
		if (sfw::getKey('s'))
		{
			playerOne.y1pos += 350 * sfw::getDeltaTime();
		}
		playerTwo.yacc = 0;
		if (sfw::getKey('i'))
		{
			playerTwo.y1pos -= 350 * sfw::getDeltaTime();
		}
		if (sfw::getKey('k'))
		{
			playerTwo.y1pos += 350 * sfw::getDeltaTime();
		}
		if (sfw::getKey('q')) break;

		sfw::drawCircle(projectile.xpos, projectile.ypos, 30);

		//draws the borders at the top and bottom of the screen
		sfw::drawLine(0, 5, SCREEN_WIDTH, 5);
		sfw::drawLine(SCREEN_WIDTH, SCREEN_HEIGHT - 5, 0, SCREEN_HEIGHT - 5);
		//draws the dotted lines in the center of the screen
		int dottedLineGap = 25, dottedLineLength = 50, dottedLineStart = 12;

		for (int i = 0; i < 9; ++i)
		{
			sfw::drawLine(SCREEN_WIDTH / 2, dottedLineStart, SCREEN_WIDTH / 2, dottedLineStart + dottedLineLength);
			dottedLineStart += (dottedLineLength + dottedLineGap);
		}

		drawRec(playerOne.x1pos, playerOne.y1pos, playerOne.x2pos, playerOne.y2pos);
		drawRec(playerTwo.x1pos, playerTwo.y1pos, playerTwo.x2pos, playerTwo.y2pos);
		
		//makes the ball pass through the left and right walls
		if (projectile.xpos < -35)
		{
			projectile.xpos = 400;
			projectile.ypos = 300;
			projectile.xvel = 0;
			projectile.yvel = 0;
			playerTwo.score++;
			if (playerTwo.score == 5)
			{
				sfw::termContext();
				std::cout << "Player Two is the winner!" << std::endl;
				system("pause");
				std::cout << "Press q to quit or r to restart. ";

				char input;
				std::cin >> input;
				if (input == 'q')
				{
					// quit
					isRunning = false;
				}
				else if (input == 'r')
				{
					// restart the game
					playerOne.score = 0;
					playerTwo.score = 0;
					sfw::initContext(SCREEN_WIDTH, SCREEN_HEIGHT, "Michael");
				}
			}
		}
		if (projectile.xpos > 830)
		{
			projectile.xpos = 400;
			projectile.ypos = 300;
			projectile.xvel = 0;
			projectile.yvel = 0;
			playerOne.score++;
			if (playerOne.score == 5)
			{
				sfw::termContext();
				std::cout << "Player One is the winner!" << std::endl;
				system("pause");
				std::cout << "Press q to quit or r to restart. ";

				char input;
				std::cin >> input;
				if (input == 'q')
				{
					// quit
					isRunning = false;
				}
				else if (input == 'r')
				{
					// restart the game
					playerOne.score = 0;
					playerTwo.score = 0;
					sfw::initContext(SCREEN_WIDTH, SCREEN_HEIGHT, "Michael");
				}
			}
		}
		//makes the ball rebound off the top and bottom walls
		if (projectile.ypos < 35)
		{
			projectile.ypos = 35;
			projectile.yvel = 400;
		}
		if (projectile.ypos > 565)
		{
			projectile.ypos = 565;
			projectile.yvel = -400;
		}
		//makes the ball hit the paddles and bounce off
		if (paddleCollision(playerOne, projectile))
		{
			projectile.xpos = playerOne.x2pos + 30;
			projectile.xvel = 400;
		}
		if (paddleCollision(playerTwo, projectile))
		{
			projectile.xpos = playerTwo.x1pos - 30;
			projectile.xvel = -400;
		}
		//Makes the paddles hit the walls and stop
		if (playerOne.y1pos < 5)
		{
			playerOne.y1pos = 5;
			playerOne.yvel = 0;
		}
		if (playerOne.y2pos > 595)
		{
			playerOne.y1pos = 495;
			playerOne.yvel = 0;
		}
		if (playerTwo.y1pos < 5)
		{
			playerTwo.y1pos = 5;
			playerTwo.yvel = 0;
		}
		if (playerTwo.y2pos > 595)
		{
			playerTwo.y1pos = 495;
			playerTwo.yvel = 0;
		}
		drawScore(5, 10, 5, playerOne.score, 10);
		drawScore(405, 10, 5, playerTwo.score, 10);
	}
	sfw::termContext();
}