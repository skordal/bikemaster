// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef TRIPSCREEN_H
#define TRIPSCREEN_H

#include "button.h"
#include "screen.h"

class TripScreen final : public Screen
{
	public:
		TripScreen();

		void render(Framebuffer & fb) override;
	private:
		Button backButton;
};

#endif
