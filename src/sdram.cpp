// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <stm32f7xx.h>

#include "delay.h"
#include "gpio.h"
#include "sdram.h"

// FMC banks 5 and 6 are used for SDRAM:
#define FMC				FMC_Bank5_6

// Alternative function code for FMC/SDRAM pins:
#define GPIO_AF_SDRAM	12

void SDRAM::setupGPIOs()
{
	GPIO::Pin pins[]{
		// Port C:
		{3, GPIO::Port::C},
		// Port D:
		{0, GPIO::Port::D}, {1, GPIO::Port::D}, {8, GPIO::Port::D}, {9, GPIO::Port::D},
		{10, GPIO::Port::D}, {14, GPIO::Port::D}, {15, GPIO::Port::D},
		// Port E:
		{0, GPIO::Port::E}, {1, GPIO::Port::E}, {7, GPIO::Port::E}, {8, GPIO::Port::E},
		{9, GPIO::Port::E}, {10, GPIO::Port::E}, {11, GPIO::Port::E}, {12, GPIO::Port::E},
		{13, GPIO::Port::E}, {14, GPIO::Port::E}, {15, GPIO::Port::E},
		// Port F:
		{0, GPIO::Port::F}, {1, GPIO::Port::F}, {2, GPIO::Port::F}, {3, GPIO::Port::F},
		{4, GPIO::Port::F}, {5, GPIO::Port::F}, {11, GPIO::Port::F}, {12, GPIO::Port::F},
		{13, GPIO::Port::F}, {14, GPIO::Port::F}, {15, GPIO::Port::F},
		// Port G:
		{0, GPIO::Port::G}, {1, GPIO::Port::G}, {4, GPIO::Port::G}, {5, GPIO::Port::G},
		{8, GPIO::Port::G}, {15, GPIO::Port::G},
		// Port H:
		{3, GPIO::Port::H}, {5, GPIO::Port::H},
	};

	for(GPIO::Pin & pin : pins)
	{
		pin.setAlternate(GPIO_AF_SDRAM);
		pin.setMode(GPIO::Mode::ALTERNATE);
		pin.setSpeed(GPIO::OutputSpeed::VERY_HIGH_SPEED);
	}
}

void SDRAM::initialize()
{
	RCC->AHB3ENR |= RCC_AHB3ENR_FMCEN;

	setupGPIOs();

	// Configure SDRAM parameters:
	FMC->SDCR[0] = 0
		| FMC_SDCR1_RBURST          // Enable burst read
		| FMC_SDCR1_NB              // Number of banks = 4
		| 1u << FMC_SDCR1_MWID_Pos  // Data bus width = 16 bits
		| 1u << FMC_SDCR1_NR_Pos    // 12 row address bits
		| 0u << FMC_SDCR1_NC_Pos    // 8 column address bits
		| 0u << FMC_SDCR1_RPIPE_Pos
		| 2u << FMC_SDCR1_SDCLK_Pos
		| 2u << FMC_SDCR1_CAS_Pos;
	FMC->SDTR[0] = 0
		| 1u << FMC_SDTR1_TRCD_Pos  // Row to column delay = 2
		| 1u << FMC_SDTR1_TRP_Pos   // Row precharge delay = 2
		| 1u << FMC_SDTR1_TWR_Pos   // Write recovery delay = 2
		| 5u << FMC_SDTR1_TRC_Pos   // Row cycle delay = 6
		| 3u << FMC_SDTR1_TRAS_Pos  // Self refresh time = 4
		| 6u << FMC_SDTR1_TXSR_Pos  // Exit self-refresh time = 7
		| 1u << FMC_SDTR1_TMRD_Pos; // Load mode register to active time = 2

	// Run the initialization sequence as specified in the reference manual:
	FMC->SDCMR = FMC_SDCMR_CTB1 | 1u << FMC_SDCMR_MODE_Pos;
	delay(100);

	FMC->SDCMR = FMC_SDCMR_CTB1 | 2u << FMC_SDCMR_MODE_Pos;
	while(FMC->SDSR & FMC_SDSR_BUSY);

	FMC->SDCMR = 1u << FMC_SDCMR_NRFS_Pos | FMC_SDCMR_CTB1 | 3u << FMC_SDCMR_MODE_Pos;
    while(FMC->SDSR & FMC_SDSR_BUSY);

	FMC->SDCMR = (1u << 5) << FMC_SDCMR_MRD_Pos | FMC_SDCMR_CTB1 | 4u << FMC_SDCMR_MODE_Pos;
    while(FMC->SDSR & FMC_SDSR_BUSY);

	FMC->SDRTR = 1563u << FMC_SDRTR_COUNT_Pos;
}
