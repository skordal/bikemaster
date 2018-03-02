// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include "framebuffer.h"

void Framebuffer::clear(const Color & clearColor)
{
	for(unsigned int i = 0; i < getWidth() * getHeight(); i++)
		getBuffer()[i].set(clearColor);
}

void Framebuffer::setPixel(const Point & pos, const Color & color)
{
	if(pos.getX() >= getWidth() || pos.getY() >= getHeight())
		return;

	getBuffer()[pos.getY() * getWidth() + pos.getX()] = color;
}

const Color & Framebuffer::getPixel(const Point & pos) const
{
	return getBuffer()[pos.getY() * getWidth() + pos.getX()];
}