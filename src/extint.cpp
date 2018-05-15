// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <stm32f7xx.h>

#include "gui.h"
#include "sensor.h"
#include "touchscreen.h"

// External interrupt handlers from various modules:

// EXTI0 - GUI update software interrupt
extern "C" void EXTI0_IRQHandler()
{
	GUI::get().renderAll();
	EXTI->PR |= EXTI_PR_PR0;
	(void) EXTI->PR;
}

// Wheel sensor interrupt
extern "C" void EXTI2_IRQHandler()
{
	if(EXTI->PR & EXTI_PR_PR2)
	{
		Sensor::get().interrupt();
		EXTI->PR |= EXTI_PR_PR2;
		(void) EXTI->PR;
	}
}

// External interrupts 10 - 15:
// 11 - user button (additional wheel sensor input)
// 13 - touchscreen interrupt
extern "C" void EXTI15_10_IRQHandler()
{
	if(EXTI->PR & EXTI_PR_PR13)
	{
		Touchscreen::get().interrupt();
		EXTI->PR |= EXTI_PR_PR13;
		EXTI->IMR &= ~EXTI_IMR_IM13; // Disable the interrupt until processing is complete
		(void) EXTI->PR;
	}

	if(EXTI->PR & EXTI_PR_PR11)
	{
		Sensor::get().interrupt();
		EXTI->PR |= EXTI_PR_PR11;
		(void) EXTI->PR;
	}
}
