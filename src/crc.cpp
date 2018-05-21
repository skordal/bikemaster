// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <stm32f7xx.h>
#include "crc.h"

uint32_t crc32(const uint32_t * data, unsigned int size)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_CRCEN;

	CRC->CR |= CRC_CR_RESET;
	while(CRC->CR & CRC_CR_RESET);

	size &= 0xfffffffc;
	size >>= 2;

	for(unsigned int i = 0; i < size; ++i)
		CRC->DR = data[i];

	return CRC->DR;
}