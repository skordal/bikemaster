// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include "button.h"
#include "gui.h"
#include "images.h"
#include "screenmanager.h"
#include "tripscreen.h"

TripScreen::TripScreen()
	: backButton(Images::Buttons::backButton(),
		[](void *){ GUI::get().setScreen(ScreenManager::get().getScreen(ScreenManager::Screen::MAIN));})
{
	setButton(0, &backButton);
}

void TripScreen::render(Framebuffer & fb)
{
	renderButtons(fb);
}

