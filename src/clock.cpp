// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <stm32f7xx.h>

#include "clock.h"
#include "debug.h"
#include "power.h"

void Clock::initialize()
{
	// Enable the HSE clock source:
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY));

	// Configure and enable the main PLL:
	// - P = 2: This causes the SYSCLK to be 200 MHz
	// - Q = 8: This causes the SDMMC clock to be 50 MHz
	RCC->PLLCFGR = RCC_PLLCFGR_PLLSRC_HSE
		| 8u << RCC_PLLCFGR_PLLQ_Pos
		| 0u << RCC_PLLCFGR_PLLP_Pos    // Setting 0 corresponds to P = 2
		| 400u << RCC_PLLCFGR_PLLN_Pos  // N = 400
		| 25u  << RCC_PLLCFGR_PLLM_Pos; // M = 25
	RCC->CR |= RCC_CR_PLLON;

	// Configure and enable the SAI PLL:
	RCC->PLLSAICFGR = 0
		| 1u << RCC_PLLSAICFGR_PLLSAIP_Pos    // Setting 1 corresponds to P = 4
		| 5u << RCC_PLLSAICFGR_PLLSAIR_Pos    // R = 5
		| 2u << RCC_PLLSAICFGR_PLLSAIQ_Pos    // Q = 2 (not used)
		| 192u << RCC_PLLSAICFGR_PLLSAIN_Pos; // N = 192
	RCC->CR |= RCC_CR_PLLSAION;

	// Enable overdrive mode in the power module to allow running on high frequencies:
	Power::get().enableOverdrive();

	// Set correct flash latency before changing MCU clock source:
	FLASH->ACR = FLASH_ACR_ARTEN | FLASH_ACR_PRFTEN
		| FLASH_ACR_LATENCY_6WS << FLASH_ACR_LATENCY_Pos;

	// Wait for the PLLs to finish starting:
	while(!(RCC->CR & RCC_CR_PLLRDY));
	while(!(RCC->CR & RCC_CR_PLLSAIRDY));

	// Configure prescalers and switch system clock source to the main PLL:
	RCC->CFGR = 0
		| 25u << RCC_CFGR_RTCPRE_Pos
		| RCC_CFGR_PPRE2_DIV2
		| RCC_CFGR_PPRE1_DIV4
		| RCC_CFGR_SW_PLL;
	while((RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_PLL);
}
