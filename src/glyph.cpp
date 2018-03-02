// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include "glyph.h"

Glyph::Glyph(unsigned int width, unsigned int height, unsigned int offsetY, const uint8_t * data)
	: width(width), height(height), offsetY(offsetY), data(data)
{

}

void Glyph::render(Framebuffer & fb, const Point & pos, const Color & color) const
{
	unsigned int startY = pos.getY() + offsetY;
	unsigned int startX = pos.getX();

	for(unsigned int y = 0; y < height; ++y)
	{
		for(unsigned int x = 0; x < width; ++x)
		{
			Color pixelColor(color);
			pixelColor.setA(data[y * width + x]);
			if(data[y * width + x] != 0)
				fb.setPixel(Point(startX + x, startY + y), pixelColor);
		}
	}
}
