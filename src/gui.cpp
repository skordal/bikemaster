// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include "config.h"
#include "gui.h"
#include "lcd.h"

GUI & GUI::initialize(Framebuffer * framebuffers[2])
{
	static GUI gui(framebuffers);
	return gui;
}

GUI::GUI(Framebuffer * framebuffers[2])
	: framebuffers(framebuffers), activeFramebuffer(0)
{
	frontbuffer().clear();
	backbuffer().clear();

	LCD::get().getLayer(0).enable(0, 0, CONFIG_FRAMEBUFFER_WIDTH, CONFIG_FRAMEBUFFER_HEIGHT,
		framebuffers[activeFramebuffer]);
}

void GUI::swapBuffers()
{
	activeFramebuffer ^= 1;
	LCD::get().getLayer(0).setFramebuffer(framebuffers[activeFramebuffer]);
}
