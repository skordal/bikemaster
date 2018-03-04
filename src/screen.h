// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef SCREEN_H
#define SCREEN_H

#include "framebuffer.h"

class Screen
{
	public:
		virtual void render(Framebuffer & fb) = 0;
		virtual Color getBackground() const { return Color(0, 0, 35); }
};

#endif
