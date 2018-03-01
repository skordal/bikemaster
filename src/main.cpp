// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <stm32f7xx.h>
#include <new>

#include "clock.h"
#include "config.h"
#include "debug.h"
#include "framebuffer.h"
#include "gpio.h"
#include "gui.h"
#include "lcd.h"
#include "sdram.h"

static Framebuffer * framebuffers[2];

int main()
{
	Debug::stream() << "Bikemaster initializing..." << Debug::endl();

	// Configure some processor settings:
	SCB->SCR |= SCB_SCR_SEVONPEND_Msk; // Events are sent on pending interrupts
	SCB_EnableICache();                // Enable instruction cache
	SCB_EnableDCache();                // Enable data cache

	// Enable access to FPU registers:
	SCB->CPACR |= 0xfu << 20;
	// Enable automatic (lazy) saving of floating point state in interrupts:
	FPU->FPCCR |= FPU_FPCCR_ASPEN_Msk | FPU_FPCCR_LSPEN_Msk;
	__DSB(); __ISB();

	// Enable interrupts early, since some initialization procedures use interrupts:
	__enable_irq();

	// Set up all the clocks:
	Clock::initialize();

	// Enable the external SDRAM:
	SDRAM::initialize();

	// Create framebuffers in SDRAM:
	framebuffers[0] = new (CONFIG_FRAMEBUFFER_ADDRESS(0)) StaticFramebuffer<480, 272>;
    framebuffers[1] = new (CONFIG_FRAMEBUFFER_ADDRESS(1)) StaticFramebuffer<480, 272>;

	// Initialize the LCD:
	LCD::get().enable();

	// Initialize the GUI:
	GUI::initialize(framebuffers);

	// Turn on the status LED:
	GPIO::Pin statusLED(1, GPIO::Port::I);
	statusLED.setMode(GPIO::Mode::OUTPUT);
	statusLED.clear(); // The LED is active-low.

	Debug::stream() << "Initialization complete!" << Debug::endl();
	while(true) __WFE();
}
