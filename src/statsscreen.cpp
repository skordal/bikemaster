// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include "gui.h"
#include "images.h"
#include "screenmanager.h"
#include "statsscreen.h"

StatsScreen::StatsScreen()
	: backButton(Images::Buttons::backButton(),
		[](void *){ GUI::get().setScreen(ScreenManager::get().getScreen(ScreenManager::Screen::MAIN));})
{
	addButton(0, &backButton);
}

void StatsScreen::render(Framebuffer & fb)
{
	renderButtons(fb);
}
