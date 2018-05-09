// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <stm32f7xx.h>

#include "config.h"
#include "gpio.h"
#include "sensor.h"

extern "C" void TIM3_IRQHandler()
{
	TIM3->SR &= ~TIM_SR_UIF;
	EXTI->IMR &= ~EXTI_IMR_IM11;
	Sensor::get().timeout();
}

extern "C" void TIM4_IRQHandler()
{
	TIM4->SR &= ~TIM_SR_UIF;
	Sensor::get().timerInterrupt();
}

extern "C" void EXTI15_10_IRQHandler()
{
	if(EXTI->PR & EXTI_PR_PR11)
	{
		Sensor::get().interrupt();
		EXTI->PR |= EXTI_PR_PR11;
		(void) EXTI->PR;
		//EXTI->IMR &= ~EXTI_IMR_IM11;
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

	// Use timer 3 as timeout timer:
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->DIER = TIM_DIER_UIE;
	TIM3->PSC = 49999; // Provides a 2 kHz timer clock
	NVIC_SetPriority(TIM3_IRQn, CONFIG_SENSOR_TIMER_IRQ_PRIORITY);
	NVIC_EnableIRQ(TIM3_IRQn);

	// Use timer 4 as sensor timer:
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	TIM4->DIER = TIM_DIER_UIE;
	TIM4->PSC = 49999; // Provides a 2 kHz timer clock
	TIM4->ARR = static_cast<unsigned int>((WHEEL_CIRCUMFERENCE / MINIMUM_SPEED) * 2000.0f);
	NVIC_SetPriority(TIM4_IRQn, CONFIG_SENSOR_TIMER_IRQ_PRIORITY);
	NVIC_EnableIRQ(TIM4_IRQn);

	// Two timers are used to prevent excessive speeds being reported if the
	// timeout fires just before the wheel sensor triggers.

	initialized = true;
}

void Sensor::interrupt()
{
	TIM3->CR1 &= ~TIM_CR1_CEN; // Stop the timeout timer
	//TIM4->CR1 &= ~TIM_CR1_CEN; // Stop the timing timer

	if(!speedTimerOverflow && (TIM4->CR1 & TIM_CR1_CEN))
	{
		TIM4->CR1 &= ~TIM_CR1_CEN;
        TIM4->SR &= ~TIM_SR_UIF; // If the interrupt has just triggered, reset it.
        speedTimerOverflow = false;

		speed = WHEEL_CIRCUMFERENCE / (TIM4->CNT / 2000.0f);
		TIM3->ARR = TIM4->CNT + 2000U;
	} else {
		speed = 0.0f;
		speedTimerOverflow = false;
		TIM3->ARR = static_cast<unsigned int>((WHEEL_CIRCUMFERENCE / MINIMUM_SPEED) * 1000.0f);
	}

	TIM3->CNT = 0;
	TIM3->CR1 = TIM_CR1_OPM | TIM_CR1_CEN;

	TIM4->CNT = 0;
	TIM4->CR1 = TIM_CR1_OPM | TIM_CR1_CEN;

	++revolutions;
}

void Sensor::timeout()
{
	float reduction = calculateSpeedReduction();
	if(speed - reduction > 0.0f)
		speed -= reduction;
	else
		speed = 0.0f;

	if(speed > MINIMUM_SPEED)
	{
		TIM3->CNT = 0;
		TIM3->ARR = static_cast<unsigned int>((WHEEL_CIRCUMFERENCE / speed) * 2000.0f) + 1000U;
        TIM3->CR1 = TIM_CR1_OPM | TIM_CR1_CEN;
	} else
		speed = 0.0f;

	EXTI->IMR |= EXTI_IMR_IM11;
}

float Sensor::calculateSpeedReduction() const
{
	return speed * 0.9f;
}
