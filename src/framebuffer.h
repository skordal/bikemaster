// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstring>

#include "color.h"

class Framebuffer
{
	public:
		void clear(const Color & clearColor = Color::black());

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual Color * getBuffer() = 0;
		virtual const Color * getBuffer() const = 0;
};

template<unsigned int W, unsigned int H>
class StaticFramebuffer : public Framebuffer
{
	public:
		StaticFramebuffer() : Framebuffer() {}

		unsigned int getWidth() const { return W; }
		unsigned int getHeight() const { return H; }

		Color * getBuffer() { return buffer; }
		const Color * getBuffer() const { return buffer; }
	private:
		Color buffer[W * H];
};

#endif
