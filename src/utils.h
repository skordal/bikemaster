// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef UTILS_H
#define UTILS_H

#include "color.h"
#include "framebuffer.h"
#include "point.h"

namespace Utils
{
	enum class CircleDrawingMode
	{
		UPPER_SEMICIRCLE,
		LOWER_SEMICIRCLE,
		FULL
	};

    void drawCircle(Framebuffer & fb, const Point & origin, unsigned int r, const Color & color,
		CircleDrawingMode mode = CircleDrawingMode::FULL);
	void drawLine(Framebuffer & fb, const Point & start, const Point & end,
		const Color & color);
	void drawRectangle(Framebuffer & fb, const Point & start, unsigned int width, unsigned int height,
		const Color & color);
	void fillRectangle(Framebuffer & fb, const Point & start, unsigned int width, unsigned int height,
		const Color & color);

	template<typename T> T abs(T value)
	{
		if(value < 0)
			return -value;
		else
			return value;
	}
}

#endif