// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef INITSCREEN_H
#define INITSCREEN_H

#include "color.h"
#include "screen.h"

class InitScreen : public Screen
{
	public:
		void render(Framebuffer & fb);
		Color getBackground() const { return Color(0, 0, 35); }
};

#endif
