// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef IMAGE_H
#define IMAGE_H

#include "framebuffer.h"

class Image
{
	public:
		virtual void render(Framebuffer & fb) const = 0;
};

#endif
