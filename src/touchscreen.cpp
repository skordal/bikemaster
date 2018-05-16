// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <stm32f7xx.h>

#include "config.h"
#include "debug.h"
#include "gpio.h"
#include "touchscreen.h"

#define GPIO_AF_I2C3	4u

extern "C" void I2C3_EV_IRQHandler()
{
	if((I2C3->CR1 & I2C_CR1_RXIE) && (I2C3->ISR & I2C_ISR_RXNE))
	{
		Touchscreen::get().currentTransfer.setData(I2C3->RXDR);
		I2C3->CR1 &= ~I2C_CR1_RXIE;
	}

	if((I2C3->CR1 & I2C_CR1_TXIE) && (I2C3->ISR & I2C_ISR_TXE))
	{
		I2C3->TXDR = Touchscreen::get().currentTransfer.getData();
		I2C3->CR1 &= ~I2C_CR1_TXIE;
		I2C3->CR1 |= I2C_CR1_STOPIE;
	}

	if((I2C3->CR1 & I2C_CR1_STOPIE) && (I2C3->ISR & I2C_ISR_STOPF))
	{
		I2C3->ICR = I2C_ICR_STOPCF;

		if(Touchscreen::get().currentTransfer.type == Touchscreen::I2CTransfer::Type::READ)
		{
			if(!(I2C3->CR2 & I2C_CR2_RD_WRN))
			{
				// Start a read transfer to read data from a register:
				I2C3->CR2 = I2C_CR2_AUTOEND | 1u << I2C_CR2_NBYTES_Pos | I2C_CR2_RD_WRN | Touchscreen::TOUCHSCREEN_ADDRESS;
				I2C3->CR1 |= I2C_CR1_RXIE;
				I2C3->CR2 |= I2C_CR2_START;
			} else {
				I2C3->CR1 &= ~(I2C_CR1_STOPIE | I2C_CR1_RXIE | I2C_CR1_TXIE);
				Touchscreen::get().finishTransfer();
			}
		} else {
			I2C3->CR1 &= ~(I2C_CR1_STOPIE | I2C_CR1_RXIE | I2C_CR1_TXIE);
			Touchscreen::get().finishTransfer();
		}
	}
}

Touchscreen & Touchscreen::get()
{
	static Touchscreen ts;
	return ts;
}

void Touchscreen::initialize()
{
	// Turn on required peripherals:
	RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    I2C3->CR1 &= ~(I2C_CR1_PE_Msk);

	get().initializeGPIO();
	get().initializeI2C();
	get().configureTouch();
}

void Touchscreen::initializeGPIO()
{
	// Initialize I2C pins:
	GPIO::Pin i2cPins[]{{7, GPIO::Port::H}, {8, GPIO::Port::H}};
	for(GPIO::Pin & pin : i2cPins)
	{
		pin.setAlternate(GPIO_AF_I2C3);
		pin.setSpeed(GPIO::OutputSpeed::VERY_HIGH_SPEED);
		pin.setPullMode(GPIO::PullMode::PULL_UP);
		pin.setType(GPIO::OutputType::OPEN_DRAIN);
		pin.setMode(GPIO::Mode::ALTERNATE);
	}

	// Initialize the touchscreen interrupt pin:
	GPIO::Pin irqPin{13, GPIO::Port::I};
	irqPin.setMode(GPIO::Mode::INPUT);
	SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PI;
	EXTI->FTSR |= EXTI_FTSR_TR13;
	EXTI->IMR |= EXTI_IMR_IM13;
    NVIC_SetPriority(EXTI15_10_IRQn, CONFIG_TOUCHSCREEN_IRQ_PRIORITY);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void Touchscreen::initializeI2C()
{
	I2C3->TIMINGR = 0x00401959; // Magical value calculated by CubeMX
	I2C3->CR1 = I2C_CR1_PE;
	NVIC_SetPriority(I2C3_EV_IRQn, CONFIG_TOUCHSCREEN_I2C_IRQ_PRIORITY); // I2C events
	NVIC_EnableIRQ(I2C3_EV_IRQn);
}

void Touchscreen::configureTouch()
{
	// Checks if the interrupt is enabled, and enables it if not:
	auto intcheck = [](uint8_t data) {
		if(data != 0)
			Touchscreen::get().writeRegister(REGADDR_MODE, 0, nullptr);
	};

	// Check if the interrupt is enabled, and enable it if not:
	readRegister(REGADDR_MODE, intcheck);
}

void Touchscreen::interrupt()
{
	// Gather information about the interrupt:
	readRegister(REGADDR_STATUS, [](uint8_t data) {
		Touchscreen::get().readRegister(REGADDR_TOUCHXH, [](uint8_t data) {
			Touchscreen::get().currentEvent.y = (data & 0xf) << 8;
			Touchscreen::get().readRegister(REGADDR_TOUCHXL, [](uint8_t data) {
				Touchscreen::get().currentEvent.y |= data;
				Touchscreen::get().readRegister(REGADDR_TOUCHYH, [](uint8_t data) {
					Touchscreen::get().currentEvent.x = (data & 0xf) << 8;
					Touchscreen::get().readRegister(REGADDR_TOUCHYL, [](uint8_t data) {
						Touchscreen::get().currentEvent.x |= data;
						if(Touchscreen::get().listener != nullptr)
							Touchscreen::get().listener->handleTouchscreenEvent(Touchscreen::get().currentEvent);
                        EXTI->IMR |= EXTI_IMR_IM13;
					});
				});
			});
		});
	});
}

void Touchscreen::readRegister(uint8_t reg, void (*callback)(uint8_t))
{
	if(!transferActive)
	{
		transferActive = true;

		currentTransfer.type = I2CTransfer::Type::READ;
        currentTransfer.setRegister(reg);
		currentTransfer.readCallback = callback;

		startTransfer();
	}
}

void Touchscreen::writeRegister(uint8_t reg, uint8_t value, void (*callback)())
{
	if(!transferActive)
	{
		transferActive = true;

		currentTransfer.type = I2CTransfer::Type::WRITE;
        currentTransfer.setRegister(reg);
		currentTransfer.setData(value);
		currentTransfer.writeCallback = callback;

		startTransfer();
	}
}

void Touchscreen::startTransfer()
{
	// The initial state is set by readRegister() or writeRegister() at the start of a transfer.
	if(currentTransfer.type == I2CTransfer::Type::READ)
	{
		I2C3->CR2 = I2C_CR2_AUTOEND | 1u << I2C_CR2_NBYTES_Pos | TOUCHSCREEN_ADDRESS;
		I2C3->TXDR = Touchscreen::get().currentTransfer.getRegister();
		I2C3->CR1 |= I2C_CR1_STOPIE;
		I2C3->CR2 |= I2C_CR2_START;
	} else {
		I2C3->CR2 = I2C_CR2_AUTOEND | 2u << I2C_CR2_NBYTES_Pos | TOUCHSCREEN_ADDRESS;
		I2C3->TXDR = Touchscreen::get().currentTransfer.getRegister();
		I2C3->CR1 |= I2C_CR1_TXIE;
		I2C3->CR2 |= I2C_CR2_START;
	}
}

void Touchscreen::finishTransfer()
{
	transferActive = false; // Allow starting a new transfer from callback

	if(currentTransfer.type == I2CTransfer::Type::READ)
	{
		if(currentTransfer.readCallback != nullptr)
			currentTransfer.readCallback(currentTransfer.getData());
	} else {
		if(currentTransfer.writeCallback != nullptr)
			currentTransfer.writeCallback();
	}
}
