// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef FONT_H
#define FONT_H

#include "glyph.h"
#include "framebuffer.h"
#include "lut.h"
#include "point.h"

class Font final
{
	public:
		static Font & getDefault();

		unsigned int getHeight() const { return 20; }
		unsigned int getWidth(const wchar_t * text) const;

		void render(Framebuffer & fb, const Point & pos, const wchar_t * text, const Color & color = Color::white()) const;
	private:
		Font(const LUT<wchar_t, const Glyph *> & glyphTable);
		const LUT<wchar_t, const Glyph *> & glyphTable;

		static const unsigned int WHITESPACE_WIDTH = 10;
		static const unsigned int CHARACTER_SPACING = 2;
};

#endif
