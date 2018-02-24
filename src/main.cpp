// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <stm32f7xx.h>

#include "clock.h"
#include "debug.h"
#include "gpio.h"
#include "sdram.h"

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

	// Enable interrupts, some initialization procedures use interrupts early on:
	__enable_irq();

	// Set up all the clocks:
	Clock::initialize();

	// Enable the external SDRAM:
	SDRAM::initialize();

	// Turn on the status LED:
	GPIO::Pin statusLED(1, GPIO::Port::I);
	statusLED.setMode(GPIO::Mode::OUTPUT);
	statusLED.clear(); // The LED is active-low.

	Debug::stream() << "Initialization complete!" << Debug::endl();
	while(true) __WFE();
}
