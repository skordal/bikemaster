// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include "screenmanager.h"

ScreenManager & ScreenManager::get()
{
	static ScreenManager sm;
	return sm;
}

Screen * ScreenManager::getScreen(ScreenManager::Screen type)
{
	switch(type)
	{
		case ScreenManager::Screen::INIT:
			return &initScreen;
		case ScreenManager::Screen::MAIN:
			return &mainScreen;
		case ScreenManager::Screen::STATS:
			return &statsScreen;
		case ScreenManager::Screen::TRIP:
			return &tripScreen;
		default:
			return nullptr;
	}
}
