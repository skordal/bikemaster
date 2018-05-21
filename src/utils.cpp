// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include "utils.h"

// Private namespace members:
namespace Utils
{
	static void plotLineNegative(Framebuffer & fb, const Point & start, const Point & end, const Color & color);
	static void plotLinePositive(Framebuffer & fb, const Point & start, const Point & end, const Color & color);
}

void Utils::plotLineNegative(Framebuffer & fb, const Point & start, const Point & end, const Color & color)
{
	int dx = end.getX() - start.getX();
	int dy = end.getY() - start.getY();
	int yi = dy < 0 ? -1 : 1;

	if(dy < 0)
		dy = -dy;

	int D = 2 * dy - dx;
	int y = start.getY();

	for(unsigned int x = start.getX(); x < end.getX(); ++x)
	{
		fb.setPixel(Point(x, y), color);
		if(D > 0)
		{
			y += yi;
			D -= 2 * dx;
		}

		D += 2 * dy;
	}
}

void Utils::plotLinePositive(Framebuffer & fb, const Point & start, const Point & end, const Color & color)
{
	int dx = end.getX() - start.getX();
	int dy = end.getY() - start.getY();
	int xi = dx < 0 ? -1 : 1;

	if(dx < 0)
		dx = -dx;

	int D = 2 * dx - dy;
	int x = start.getX();

	for(unsigned int y = start.getY(); y < end.getY(); ++y)
	{
		fb.setPixel(Point(x, y), color);
		if(D > 0)
		{
			x += xi;
			D -= 2 * dy;
		}

		D += 2 * dx;
	}
}

void Utils::drawLine(Framebuffer & fb, const Point & start, const Point & end, const Color & color)
{
	// Convert coordinates to signed integers:
	int x0 = start.getX(), y0 = start.getY();
	int x1 = end.getX(), y1 = end.getY();

	if(abs(y1 - y0) < abs(x1 - x0))
	{
		if(x0 > x1)
			Utils::plotLineNegative(fb, end, start, color);
		else
			Utils::plotLineNegative(fb, start, end, color);
	} else {
		if(y0 > y1)
			Utils::plotLinePositive(fb, end, start, color);
		else
			Utils::plotLinePositive(fb, start, end, color);
	}
}


void Utils::drawCircle(Framebuffer & fb, const Point & origin, unsigned int r, const Color & color,
	Utils::CircleDrawingMode mode)
{
	bool drawUpper = mode == Utils::CircleDrawingMode::FULL
		|| mode == Utils::CircleDrawingMode::UPPER_SEMICIRCLE;
	bool drawLower = mode == Utils::CircleDrawingMode::FULL
		|| mode == Utils::CircleDrawingMode::LOWER_SEMICIRCLE;

	int plotX = r, plotY = 0;
	int p = 1 - r;

	fb.setPixel(Point(origin.getX() - r, origin.getY()), color);
	fb.setPixel(Point(origin.getX() + r, origin.getY()), color);

	if(drawLower)
		fb.setPixel(Point(origin.getX(), origin.getY() + r), color);
	if(drawUpper)
		fb.setPixel(Point(origin.getX(), origin.getY() - r), color);

	while(plotX > plotY)
	{
		++plotY;

		if(p <= 0)
			p = p + 2 * plotY + 1;
		else {
			--plotX;
			p = p + 2 * plotY - 2 * plotX + 1;
		}

		if(plotX < plotY)
			break;

		if(drawLower)
		{
			fb.setPixel(Point(plotX + origin.getX(), plotY + origin.getY()), color);
			fb.setPixel(Point(-plotX + origin.getX(), plotY + origin.getY()), color);
		}

		if(drawUpper)
		{
			fb.setPixel(Point(plotX + origin.getX(), -plotY + origin.getY()), color);
			fb.setPixel(Point(-plotX + origin.getX(), -plotY + origin.getY()), color);
		}

		if(plotX != plotY)
		{
			if(drawLower)
			{
				fb.setPixel(Point(plotY + origin.getX(), plotX + origin.getY()), color);
				fb.setPixel(Point(-plotY + origin.getX(), plotX + origin.getY()), color);
			}

			if(drawUpper)
			{
				fb.setPixel(Point(plotY + origin.getX(), -plotX + origin.getY()), color);
				fb.setPixel(Point(-plotY + origin.getX(), -plotX + origin.getY()), color);
			}
		}
	}
}

void Utils::drawRectangle(Framebuffer & fb, const Point & start, unsigned int width, unsigned int height,
	const Color & color)
{
	drawLine(fb, start, start.offset(width, 0), color);
	drawLine(fb, start.offset(width, 0), start.offset(width, height), color);
	drawLine(fb, start.offset(0, height), start.offset(width, height), color);
	drawLine(fb, start, start.offset(0, height), color);
}

void Utils::fillRectangle(Framebuffer & fb, const Point & start, unsigned int width, unsigned int height,
	const Color & color)
{
	for(unsigned int y = start.getY(); y < start.getY() + height; ++y)
		for(unsigned int x = start.getX(); x < start.getX() + width; ++x)
			fb.setPixel(Point(x, y), color);
}
