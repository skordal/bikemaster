// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <stm32f7xx.h>

#include "config.h"
#include "debug.h"
#include "gpio.h"
#include "sensor.h"

extern "C" void TIM3_IRQHandler()
{
	if(TIM3->SR & TIM_SR_UIF)
	{
		TIM3->SR &= ~TIM_SR_UIF;
        EXTI->IMR |= EXTI_IMR_IM11;
		Sensor::get().timerTicks++;
	}
}

extern "C" void EXTI15_10_IRQHandler()
{
	if(EXTI->PR & EXTI_PR_PR11)
	{
		EXTI->PR |= EXTI_PR_PR11;
		EXTI->IMR &= ~EXTI_IMR_IM11;
		Sensor::get().interrupt();
	}
}

Sensor & Sensor::get()
{
	static Sensor sensor;
	if(!sensor.initialized)
		sensor.initialize();
	return sensor;
}

void Sensor::initialize()
{
	// PI11 is connected to the user button:
	GPIO::Pin buttonPin(11, GPIO::Port::I);
	buttonPin.setMode(GPIO::Mode::INPUT);

	// Use the user button as a temporary sensor input:
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PI;
	EXTI->RTSR |= EXTI_RTSR_TR11;
	EXTI->IMR |= EXTI_IMR_IM11;

	NVIC_SetPriority(EXTI15_10_IRQn, CONFIG_SENSOR_IRQ_PRIORITY);
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	// Use timer 3 to provide timing information:
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->PSC = 9999; // Provides a 10 Khz clock signal
	TIM3->ARR = 1000; // Gives a 10 Hz timer interrupt
    TIM3->DIER = TIM_DIER_UIE;
	TIM3->CR1 = TIM_CR1_CEN;
	NVIC_SetPriority(TIM3_IRQn, CONFIG_SENSOR_TIMER_IRQ_PRIORITY);
	NVIC_EnableIRQ(TIM3_IRQn);
}

float Sensor::getSpeed()
{
	__disable_irq();
	unsigned long time = timerTicks - prevTimerTicks;

	if((WHEEL_CIRCUMFERENCE / 2.0f) / (0.1f * time) < speed)
		speed = (WHEEL_CIRCUMFERENCE / 2.0f) / (0.1f * time);
	if(speed < MIN_SPEED)
		speed = 0.0f;

	__enable_irq();
	return speed;
}

void Sensor::interrupt()
{
	++halfRevolutions;

	// Time since last timer tick:
	unsigned long time = timerTicks - prevTimerTicks;
	if(time == 0)
		return;

	speed = (WHEEL_CIRCUMFERENCE / 2.0f) / (0.1f * time);
	prevTimerTicks = timerTicks;
}
