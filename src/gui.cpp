// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <stm32f7xx.h>

#include "config.h"
#include "debug.h"
#include "gui.h"
#include "lcd.h"

extern "C" void EXTI0_IRQHandler()
{
	EXTI->PR |= EXTI_PR_PR0;
    GUI::get().renderAll();
}

GUI & GUI::get()
{
	static GUI gui;
	return gui;
}

void GUI::initialize(Framebuffer * framebuffers[2])
{
	this->framebuffers[0] = framebuffers[0];
    this->framebuffers[1] = framebuffers[1];

	frontbuffer().clear();
	backbuffer().clear();

	LCD::get().getLayer(0).enable(0, 0, CONFIG_FRAMEBUFFER_WIDTH, CONFIG_FRAMEBUFFER_HEIGHT,
		framebuffers[activeFramebuffer]);

	// Enable the DMA2D accelerator:
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2DEN;

	// Enable the EXTI0 software interrupt to be used to request redraws:
	EXTI->IMR |= EXTI_IMR_IM0;
	EXTI->PR |= EXTI_PR_PR0;
	NVIC_SetPriority(EXTI0_IRQn, CONFIG_GUI_REDRAW_IRQ_PRIORITY);
	NVIC_EnableIRQ(EXTI0_IRQn);
}

void GUI::update()
{
	// Trigger a redraw interrupt when able:
	EXTI->SWIER |= EXTI_SWIER_SWIER0;
}

void GUI::renderAll()
{
	if(framebuffers[0] == nullptr || framebuffers[1] == nullptr)
		return;

	if(currentScreen != nullptr)
		currentScreen->render(backbuffer());
	swapBuffers();
}

void GUI::swapBuffers()
{
	activeFramebuffer ^= 1;
	LCD::get().getLayer(0).setFramebuffer(framebuffers[activeFramebuffer]);
}
