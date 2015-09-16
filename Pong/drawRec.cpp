#include "sfwdraw.h"
#include "drawRec.h"

void drawRec(float x1, float y1, float x2, float y2)
{
	// A line
	sfw::drawLine(x1, y1, x1, y2);
	// B line
	sfw::drawLine(x1, y2, x2, y2);
	// C line
	sfw::drawLine(x2, y1, x2, y2);
	// D line
	sfw::drawLine(x1, y1, x2, y1);
}