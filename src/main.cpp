// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <new>
#include <stm32f7xx.h>

#include "clock.h"
#include "config.h"
#include "debug.h"
#include "font.h"
#include "framebuffer.h"
#include "gpio.h"
#include "gui.h"
#include "lcd.h"
#include "processor.h"
#include "screenmanager.h"
#include "sdram.h"
#include "sensor.h"
#include "touchscreen.h"

int main()
{
	Debug::stream() << "Bikemaster initializing..." << Debug::endl();

	// Initialize processor parameters:
	Processor::initialize();

	// Enable interrupts early, since some initialization procedures use interrupts:
	__enable_irq();

	// Set up all the clocks:
	Clock::initialize();

	// Enable the external SDRAM:
	SDRAM::initialize();

	// Create framebuffers in SDRAM:
    Framebuffer * framebuffers[2]{
		new (CONFIG_FRAMEBUFFER_ADDRESS(0)) StaticFramebuffer<CONFIG_FRAMEBUFFER_WIDTH, CONFIG_FRAMEBUFFER_HEIGHT>,
		new (CONFIG_FRAMEBUFFER_ADDRESS(1)) StaticFramebuffer<CONFIG_FRAMEBUFFER_WIDTH, CONFIG_FRAMEBUFFER_HEIGHT>};

	// Initialize the LCD:
	LCD::get().enable();

	// Initialize the touchscreen module:
	Touchscreen::get().initialize();

	// Initialize the GUI and show the initialization screen:
	GUI::get().initialize(framebuffers);
	GUI::get().setScreen(ScreenManager::get().getScreen(ScreenManager::Screen::INIT));

	// Initialize the wheel sensor module:
	Sensor::get();

	// Switch to the main screen:
	GUI::get().setScreen(ScreenManager::get().getScreen(ScreenManager::Screen::MAIN));

    // Turn on the status LED:
	GPIO::Pin statusLED(1, GPIO::Port::I);
	statusLED.setMode(GPIO::Mode::OUTPUT);
	statusLED.clear(); // The LED is active-low.

	Debug::stream() << "Initialization complete!" << Debug::endl();
	while(true) __WFE();
}
