// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <stm32f7xx.h>
#include "processor.h"

void Processor::initialize()
{
	SCB->SCR |= SCB_SCR_SEVONPEND_Msk; // Events are sent on pending interrupts
	SCB_EnableICache();                // Enable instruction cache
	SCB_EnableDCache();                // Enable data cache

	// Enable access to FPU registers:
	SCB->CPACR |= 0xfu << 20;
	// Enable automatic (lazy) saving of floating point state in interrupts:
	FPU->FPCCR |= FPU_FPCCR_ASPEN_Msk | FPU_FPCCR_LSPEN_Msk;
	__DSB(); __ISB();
}
