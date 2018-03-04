// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstring>

#include "color.h"
#include "point.h"

class Framebuffer
{
	public:
		void clear(const Color & clearColor = Color::black());

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual Color * getBuffer() = 0;
		virtual const Color * getBuffer() const = 0;

		void setPixel(const Point & pos, const Color & color);
		const Color & getPixel(const Point & pos) const;
};

template<unsigned int W, unsigned int H>
class StaticFramebuffer final : public Framebuffer
{
	public:
		StaticFramebuffer() : Framebuffer() {}

		unsigned int getWidth() const override { return W; }
		unsigned int getHeight() const override { return H; }

		Color * getBuffer() override { return buffer; }
		const Color * getBuffer() const override { return buffer; }
	private:
		Color buffer[W * H];
};

#endif
