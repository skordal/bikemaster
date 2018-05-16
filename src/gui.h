// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef GUI_H
#define GUI_H

#include "framebuffer.h"
#include "lcd.h"
#include "screen.h"
#include "touchscreen.h"

extern "C" void EXTI0_IRQHandler();
extern "C" void TIM2_IRQHandler();
extern "C" void DMA2D_IRQHandler();

class GUI final : private LCDUpdateListener, private TouchscreenListener
{
	public:
		static GUI & get();
		void initialize(Framebuffer * framebuffers[2]);

		void setScreen(Screen * screen) { currentScreen = screen; update(); }

		void update();
	private:
		GUI() : framebuffers{nullptr, nullptr}, activeFramebuffer(0), initialized(false) {}

		void renderAll();
		void animate();

		void onLCDUpdated() override;
		void handleTouchscreenEvent(const TouchscreenEvent & event) override;

		void swapBuffers();
		Framebuffer & frontbuffer() { return *framebuffers[activeFramebuffer]; }
		Framebuffer & backbuffer() { return *framebuffers[activeFramebuffer ^ 1]; }

		Screen * currentScreen;
		Color currentBackground = Color::black();

		Framebuffer * framebuffers[2];
		unsigned int activeFramebuffer = 0;

		volatile enum { STATE_WAIT_FOR_VSYNC, STATE_WAIT_FOR_CLEAR, STATE_READY } state = STATE_READY;
		volatile bool updatePending = false;

		bool initialized;

	friend void ::EXTI0_IRQHandler();
	friend void ::TIM2_IRQHandler();
	friend void ::DMA2D_IRQHandler();
};

#endif
