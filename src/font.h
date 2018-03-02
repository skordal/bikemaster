// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef FONT_H
#define FONT_H

#include "glyph.h"
#include "framebuffer.h"
#include "lut.h"
#include "point.h"

class Font
{
	public:
		static Font & getDefault();

		Font(const LUT<wchar_t, const Glyph *> & glyphTable);

		void render(Framebuffer & fb, const Point & pos, const wchar_t * text, const Color & color = Color::white()) const;
	private:
		const LUT<wchar_t, const Glyph *> & glyphTable;

		static const unsigned int WHITESPACE_WIDTH = 10;
		static const unsigned int CHARACTER_SPACING = 2;
};

#endif
