// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef SCREEN_H
#define SCREEN_H

#include "framebuffer.h"
#include "touchscreen.h"

class Screen : public TouchscreenListener
{
	public:
		virtual void render(Framebuffer & fb) = 0;
		virtual void animate() {};

		virtual void handleTouchscreenEvent(const TouchscreenEvent & event) { (void) event; }
		virtual Color getBackground() const { return Color::black(); }
};

#endif
