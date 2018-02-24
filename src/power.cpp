// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <stm32f7xx.h>
#include "power.h"

bool Power::initialized = false;

Power & Power::get()
{
	static Power module;
	if(!Power::initialized)
		Power::initialize();
	return module;
}

void Power::enableOverdrive()
{
	PWR->CR1 |= PWR_CR1_ODEN;
	while(!(PWR->CSR1 & PWR_CSR1_ODRDY));
	PWR->CR1 |= PWR_CR1_ODSWEN;
	while(!(PWR->CSR1 & PWR_CSR1_ODSWRDY));
}

void Power::initialize()
{
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	initialized = true;
}
