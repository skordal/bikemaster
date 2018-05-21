// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <stm32f7xx.h>

#include <cross_studio_io.h>

#include "config.h"
#include "debug.h"
#include "gui.h"
#include "lcd.h"

extern "C" void TIM2_IRQHandler()
{
	if(TIM2->SR & TIM_SR_UIF)
	{
		TIM2->SR &= ~TIM_SR_UIF;
		GUI::get().animate();
		GUI::get().update();
	}
}

extern "C" void DMA2D_IRQHandler()
{
	if(DMA2D->ISR & DMA2D_ISR_TCIF)
	{
		DMA2D->IFCR = DMA2D_IFCR_CTCIF;
		GUI::get().state = GUI::STATE_READY;

		if(GUI::get().updatePending)
			GUI::get().update();
	}
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

	LCD::get().getLayer(0).enable(0, 0, CONFIG_FRAMEBUFFER_WIDTH, CONFIG_FRAMEBUFFER_HEIGHT,
		framebuffers[activeFramebuffer]);
	LCD::get().setBackgroundColor(currentBackground);
	LCD::get().setListener(this);

	// Enable the DMA2D accelerator:
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2DEN;
	// Enable timer 2 as animation timer:
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	// Enable the EXTI0 software interrupt to be used to request redraws:
	EXTI->IMR |= EXTI_IMR_IM0;
	EXTI->PR |= EXTI_PR_PR0;
	NVIC_SetPriority(EXTI0_IRQn, CONFIG_GUI_REDRAW_IRQ_PRIORITY);
	NVIC_EnableIRQ(EXTI0_IRQn);

	// Set up timer 2 to provide an interrupt every 100 ms:
	TIM2->PSC = 99;    // Run the clock on a 1 MHz frequency
	TIM2->ARR = 25000; // Provide a 25 ms update interval
	TIM2->DIER = TIM_DIER_UIE;
	TIM2->CR1 = TIM_CR1_CEN;
	NVIC_SetPriority(TIM2_IRQn, CONFIG_ANIMATION_TIMER_IRQ_PRIORITY);
	NVIC_EnableIRQ(TIM2_IRQn);

	// Configure the DMA2D for use:
	NVIC_SetPriority(DMA2D_IRQn, CONFIG_DMA2D_IRQ_PRIORITY);
	NVIC_EnableIRQ(DMA2D_IRQn);

	// Register as a touchscreen listener:
	Touchscreen::get().addListener(this);
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

	if(state != STATE_READY)
	{
		updatePending = true;
		return;
	} else
		updatePending = false;

	if(currentScreen != nullptr)
	{
		if(currentBackground != currentScreen->getBackground())
		{
			currentBackground = currentScreen->getBackground();
			LCD::get().setBackgroundColor(currentBackground);
		}

		currentScreen->render(backbuffer());
	}

	swapBuffers();
}

void GUI::animate()
{
	if(currentScreen != nullptr)
		currentScreen->animate();
}

void GUI::onLCDUpdated()
{
	if(state == STATE_WAIT_FOR_VSYNC)
	{
		state = STATE_WAIT_FOR_CLEAR;

		// Clear the new backbuffer using the 2D DMA:
		DMA2D->OMAR = reinterpret_cast<uint32_t>(backbuffer().getBuffer());
		DMA2D->OPFCCR = 1u << DMA2D_OPFCCR_CM_Pos; // RGB888
		DMA2D->OCOLR = 0; // Black background
		DMA2D->NLR = backbuffer().getHeight() << DMA2D_NLR_NL_Pos | backbuffer().getWidth() << DMA2D_NLR_PL_Pos;
		DMA2D->CR = DMA2D_CR_TCIE | DMA2D_CR_START | 3u << DMA2D_CR_MODE_Pos;
	}
}

void GUI::handleTouchscreenEvent(const TouchscreenEvent & event)
{
	if(currentScreen != nullptr)
		currentScreen->handleTouchscreenEvent(event);
}

void GUI::swapBuffers()
{
	state = STATE_WAIT_FOR_VSYNC;
    activeFramebuffer ^= 1;
	LCD::get().getLayer(0).setFramebuffer(framebuffers[activeFramebuffer]);
}
