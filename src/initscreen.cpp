// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include "config.h"
#include "font.h"
#include "initscreen.h"
#include "strings.h"

void InitScreen::render(Framebuffer & fb)
{
	const wchar_t * initString = Strings::get(Strings::ID::INITIALIZING, CONFIG_GUI_LANGUAGE);

	Font & font = Font::getDefault();
	unsigned int textWidth = font.getWidth(initString);

	unsigned int xOffset = (fb.getWidth() - textWidth) / 2;
	unsigned int yOffset = (fb.getHeight() - font.getHeight()) / 2;

	font.render(fb, Point(xOffset, yOffset), initString);
}
