// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef GLYPH_H
#define GLYPH_H

#include <cstdint>

#include "color.h"
#include "framebuffer.h"
#include "lut.h"
#include "point.h"

class Glyph
{
	public:
		Glyph(unsigned int width, unsigned int height, unsigned int offsetY, const uint8_t * data);

		void render(Framebuffer & fb, const Point & pos, const Color & color) const;

		unsigned int getWidth() const { return width; }
	private:
		unsigned int width, height, offsetY;
        const uint8_t * data;
};

// All available glyphs, defined in the autogenerated glyphs.cpp file:
extern LUT<wchar_t, const Glyph *> glyphs;

#endif
