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

		virtual void setPixel(const Point & pos, const Color & color)
			{ getBuffer()[pos.getY() * getWidth() + pos.getX()] = color; }
		virtual const Color & getPixel(const Point & pos) const
			{ return getBuffer()[pos.getY() * getWidth() + pos.getX()]; }
};

class FramebufferViewport final : public Framebuffer
{
	public:
		FramebufferViewport(Framebuffer & fb, const Point & offset, unsigned int width, unsigned int height)
			: fb(fb), offset(offset), width(width), height(height) {}

		unsigned int getWidth() const override { return width; }
		unsigned int getHeight() const override { return height; }

		Color * getBuffer() override { return fb.getBuffer(); }
		const Color * getBuffer() const override { return fb.getBuffer(); }

		void setPixel(const Point & pos, const Color & color) override
			{ fb.setPixel(pos.offset(offset), color); }
		virtual const Color & getPixel(const Point & pos) const override
			{ return fb.getPixel(pos.offset(offset)); }

		void setOffset(const Point & offset) { this->offset = offset; }
		const Point & getOffset() const { return offset; }

	private:
		Framebuffer & fb;
		Point offset;
		unsigned int width, height;
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
		Color buffer[W * H] __attribute((aligned(4)));
};

#endif
