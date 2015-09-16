#include "Header.h"

bool paddleCollision(paddle playerPaddle, Ball projectile)
{
	// is within top and bottom of the paddle
	if (projectile.ypos > playerPaddle.y1pos &&
		projectile.ypos < playerPaddle.y2pos)
	{
		// has collided with paddle on x-axis
		// left paddle
		if (playerPaddle.x1pos < SCREEN_WIDTH / 2)
		{
			// check for collision on the right of the paddle
			if (projectile.xpos < playerPaddle.x2pos + 30)
			{
				return true;
			}
		}
		else // right paddle
		{
			// check for collision on the left of the paddle
			if (projectile.xpos > playerPaddle.x1pos - 30)
			{
				return true;
			}
		}
	}

	// one of the conditions failed, collision is not occurring
	return false;
}