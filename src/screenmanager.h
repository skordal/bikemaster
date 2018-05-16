// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "screen.h"

#include "initscreen.h"
#include "mainscreen.h"
#include "statsscreen.h"
#include "tripscreen.h"

class ScreenManager final
{
	public:
		enum class Screen
		{
			INIT, MAIN, STATS, TRIP
		};

		static ScreenManager & get();
		::Screen * getScreen(ScreenManager::Screen type);
	private:
		InitScreen initScreen;
		MainScreen mainScreen;
		StatsScreen statsScreen;
		TripScreen tripScreen;
};

#endif
