// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <stddef.h>
#include <stm32f7xx.h>

#include "gpio.h"

using namespace GPIO;

static GPIO_TypeDef * memory(Port port)
{
	GPIO_TypeDef * lookup[] = { GPIOA, GPIOB, GPIOC, GPIOD,
		GPIOE, GPIOF, GPIOG, GPIOH, GPIOI, GPIOJ, GPIOK };
	return lookup[static_cast<unsigned int>(port)];
}

Controller & Controller::get(Port port)
{
	// Controller instances, one per port:
	static Controller ports[]{ Port::A, Port::B, Port::C, Port::D,
		Port::E, Port::F, Port::G, Port::H, Port::I, Port::J, Port::K };

	return ports[static_cast<unsigned int>(port)];
}

Controller::Controller(Port port) : port(port)
{
	RCC->AHB1ENR |= 1 << (RCC_AHB1ENR_GPIOAEN_Pos + static_cast<unsigned int>(port));
}

void Controller::setMode(uint8_t pin, Mode mode)
{
	memory(port)->MODER &= ~(GPIO_MODER_MODER0_Msk << (pin * 2));
	memory(port)->MODER |= static_cast<unsigned int>(mode) << (pin * 2);
}

void Controller::setOutputType(uint8_t pin, OutputType type)
{
	if(type == OutputType::PUSH_PULL)
		memory(port)->OTYPER &= ~(1u << pin);
	else
		memory(port)->OTYPER |= 1u << pin;
}

void Controller::setOutputSpeed(uint8_t pin, OutputSpeed speed)
{
	memory(port)->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0_Msk << (pin * 2));
	memory(port)->OSPEEDR |= static_cast<unsigned int>(speed) << (pin * 2);
}

void Controller::setPullMode(uint8_t pin, PullMode pull)
{
	memory(port)->PUPDR &= ~(GPIO_PUPDR_PUPDR0_Msk << (pin * 2));
	memory(port)->PUPDR |= static_cast<unsigned int>(pull) << (pin * 2);
}

void Controller::setAlternate(uint8_t pin, uint8_t alternate)
{
	if(pin >= 8)
	{
		memory(port)->AFR[1] &= ~(0xffu << ((pin - 8) * 4));
		memory(port)->AFR[1] |= alternate << ((pin - 8) * 4);
	} else {
		memory(port)->AFR[0] &= ~(0xffu << (pin * 4));
		memory(port)->AFR[0] |= alternate << (pin * 4);
	}
}

void Controller::set(uint8_t pin, uint8_t value)
{
	if(value)
		memory(port)->BSRR = 1u << (GPIO_BSRR_BS_0 + pin);
	else
		memory(port)->BSRR = 1u << (GPIO_BSRR_BR_0 + pin);
}

bool Controller::read(uint8_t pin)
{
	return (memory(port)->IDR >> pin) & 1;
}
