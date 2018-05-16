// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef TRIPSCREEN_H
#define TRIPSCREEN_H

#include "screen.h"

class TripScreen final : public Screen
{
	public:
		void render(Framebuffer & fb) override;
};

#endif
