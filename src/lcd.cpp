// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <stm32f7xx.h>

#include "color.h"
#include "gpio.h"
#include "lcd.h"

// Alternate function codes for LTDC pins:
#define GPIO_AF_LCD_9	9u
#define GPIO_AF_LCD_14	14u // Because it would be too easy if they only used one AF value

static constexpr LTDC_Layer_TypeDef * layerMem(unsigned int i)
{
	return i == 0 ? LTDC_Layer1 : LTDC_Layer2;
}

void LCDLayer::enable(unsigned int x, unsigned int y, unsigned int w, unsigned int h, Framebuffer * fb)
{
	const unsigned int firstPixelX = ((LTDC->BPCR & LTDC_BPCR_AHBP_Msk) >> LTDC_BPCR_AHBP_Pos) + 1;
	const unsigned int firstPixelY = ((LTDC->BPCR & LTDC_BPCR_AVBP_Msk) >> LTDC_BPCR_AVBP_Pos) + 1;
	const unsigned int startX = firstPixelX + x;
	const unsigned int endX = startX + w - 1;

	const unsigned int startY = firstPixelY + y;
	const unsigned int endY = startY + h - 1;

	layerMem(index)->CR &= ~LTDC_LxCR_LEN_Msk;
	layerMem(index)->WHPCR = endX << LTDC_LxWHPCR_WHSPPOS_Pos
		| startX << LTDC_LxWHPCR_WHSTPOS_Pos;
	layerMem(index)->WVPCR = endY << LTDC_LxWVPCR_WVSPPOS_Pos
		| startY << LTDC_LxWVPCR_WVSTPOS_Pos;
	layerMem(index)->CFBAR = reinterpret_cast<uint32_t>(fb->getBuffer());
	layerMem(index)->CFBLR = fb->getWidth() * sizeof(Color) << LTDC_LxCFBLR_CFBP_Pos
		| (fb->getWidth() * sizeof(Color) + 3) << LTDC_LxCFBLR_CFBLL_Pos;
	layerMem(index)->CFBLNR = h;
	layerMem(index)->CR |= LTDC_LxCR_LEN;

	LCD::get().reload();
}

void LCDLayer::setFramebuffer(Framebuffer *fb)
{
	this->fb = fb;
	layerMem(index)->CFBAR = reinterpret_cast<uint32_t>(fb->getBuffer());
	layerMem(index)->CFBLR = fb->getWidth() * sizeof(Color) << LTDC_LxCFBLR_CFBP_Pos
		| (fb->getWidth() * sizeof(Color) + 3) << LTDC_LxCFBLR_CFBLL_Pos;
	LCD::get().reload();
}

LCD & LCD::get()
{
	static LCD controller;
	if(!controller.initialized)
		controller.initialize();

	return controller;
}

void LCD::enable()
{
	LTDC->GCR |= LTDC_GCR_LTDCEN;
}

void LCD::disable()
{
	LTDC->GCR &= ~LTDC_GCR_LTDCEN;
}

void LCD::setBackgroundColor(const Color & bg)
{
	LTDC->BCCR = 0
		| bg.getR() << LTDC_BCCR_BCRED_Pos
		| bg.getG() << LTDC_BCCR_BCGREEN_Pos
		| bg.getB() << LTDC_BCCR_BCBLUE_Pos;
	reload();
}

LCD::LCD() : initialized(false)
{

}

void LCD::initialize()
{
	RCC->APB2ENR |= RCC_APB2ENR_LTDCEN;
	setupGPIOs();

	// Set display parameters:
#if 0
	LTDC->SSCR = 40u << LTDC_SSCR_HSW_Pos | 9u << LTDC_SSCR_VSH_Pos;
	LTDC->BPCR = 53u << LTDC_BPCR_AHBP_Pos | 11u << LTDC_BPCR_AVBP_Pos;
	LTDC->AWCR = 533u << LTDC_AWCR_AAW_Pos | 283u << LTDC_AWCR_AAH_Pos;
	LTDC->TWCR = 563u << LTDC_TWCR_TOTALW_Pos | 285u << LTDC_TWCR_TOTALH_Pos;
#else
	LTDC->BPCR = 43u << LTDC_BPCR_AHBP_Pos | 12u << LTDC_BPCR_AVBP_Pos;
	LTDC->AWCR = 523u << LTDC_AWCR_AAW_Pos | 284u << LTDC_AWCR_AAH_Pos;
	LTDC->TWCR = 531u << LTDC_TWCR_TOTALW_Pos | 288u << LTDC_TWCR_TOTALH_Pos;
#endif

	initialized = true;
}

void LCD::setupGPIOs()
{
	GPIO::Pin pins_af14[]{
			// Port E:
			{4, GPIO::Port::E},
            // Port I:
			{9, GPIO::Port::I}, {10, GPIO::Port::I}, {13, GPIO::Port::I},
			{14, GPIO::Port::I}, {15, GPIO::Port::I},
            // Port J (J12 is not used by the LTDC):
			{0, GPIO::Port::J}, {1, GPIO::Port::J}, {2, GPIO::Port::J}, {3, GPIO::Port::J},
			{4, GPIO::Port::J}, {5, GPIO::Port::J}, {6, GPIO::Port::J}, {7, GPIO::Port::J},
			{8, GPIO::Port::J}, {9, GPIO::Port::J}, {10, GPIO::Port::J}, {11, GPIO::Port::J},
			{13, GPIO::Port::J}, {14, GPIO::Port::J}, {15, GPIO::Port::J},
            // Port K:
			{0, GPIO::Port::K}, {1, GPIO::Port::K}, {2, GPIO::Port::K}, {4, GPIO::Port::K},
			{5, GPIO::Port::K}, {6, GPIO::Port::K}, {7, GPIO::Port::K}
		};

	GPIO::Pin g12(12, GPIO::Port::G);
	g12.setAlternate(GPIO_AF_LCD_9);
	g12.setMode(GPIO::Mode::ALTERNATE);

    for(GPIO::Pin & pin : pins_af14)
	{
		pin.setAlternate(GPIO_AF_LCD_14);
		pin.setMode(GPIO::Mode::ALTERNATE);
	}

	// I12 is the display enable pin:
	GPIO::Pin displayEnable(12, GPIO::Port::I);
	displayEnable.setMode(GPIO::Mode::OUTPUT);
	displayEnable.clear();
}

void LCD::reload()
{
	LTDC->SRCR = LTDC_SRCR_VBR;
}
