// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef STATSSCREEN_H
#define STATSSCREEN_H

#include "screen.h"

class StatsScreen final : public Screen
{
	public:
		void render(Framebuffer & fb) override;
};

#endif
