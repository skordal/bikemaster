// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <stm32f7xx.h>

#include "config.h"
#include "debug.h"
#include "delay.h"

static volatile bool waiting = false;

extern "C" void TIM1_UP_TIM10_IRQHandler()
{
	if(TIM10->SR & TIM_SR_UIF)
	{
		TIM10->SR &= ~(TIM_SR_UIF);
		waiting = false;
	}
}

void delay(uint16_t usec)
{
	// Enable timer 10 clock:
	RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;

	// Configure the timer:
	TIM10->CNT = 0;             // Set the counter to 0
	TIM10->PSC = 199;           // Set the prescaler to 200, generating a 1 μs clock
	TIM10->ARR = usec;          // Set the target value
	TIM10->DIER = TIM_DIER_UIE; // Enable interrupt on update event
	TIM10->CR1 = TIM_CR1_URS | TIM_CR1_CEN | TIM_CR1_OPM;

	waiting = true;
	NVIC_SetPriority(TIM1_UP_TIM10_IRQn, CONFIG_DELAY_TIMER_IRQ_PRIORITY);
	NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
	while(waiting) __WFI();
	NVIC_DisableIRQ(TIM1_UP_TIM10_IRQn);
}
