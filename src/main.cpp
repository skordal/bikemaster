// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <stm32f7xx.h>

#include "clock.h"
#include "debug.h"
#include "gpio.h"

int main()
{
	Debug::stream() << "Bikemaster initializing..." << Debug::endl();
	Clock::initialize();

	// Turn on the status LED:
	GPIO::Pin statusLED(1, GPIO::Port::I);
	statusLED.setMode(GPIO::Mode::OUTPUT);
	statusLED.clear(); // The LED is active-low.

	Debug::stream() << "Initialization complete!" << Debug::endl();
	while(true) __WFE();
}
