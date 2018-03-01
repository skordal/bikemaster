// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef GUI_H
#define GUI_H

#include "framebuffer.h"
#include "screen.h"

extern "C" void EXTI0_IRQHandler();

class GUI final
{
	public:
		static GUI & get();
		void initialize(Framebuffer * framebuffers[2]);

		void setScreen(Screen * screen) { currentScreen = screen; update(); }

		void update();
	private:
		GUI() : framebuffers{nullptr, nullptr}, activeFramebuffer(0), initialized(false) {}

		void renderAll();

		void swapBuffers();
		Framebuffer & frontbuffer() { return *framebuffers[activeFramebuffer]; }
		Framebuffer & backbuffer() { return *framebuffers[activeFramebuffer ^ 1]; }

		Screen * currentScreen;

		Framebuffer * framebuffers[2];
		unsigned int activeFramebuffer;

		bool initialized;
	friend void ::EXTI0_IRQHandler();
};

#endif
