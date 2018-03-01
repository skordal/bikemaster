// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef GUI_H
#define GUI_H

#include "framebuffer.h"

class GUI final
{
	public:
		static GUI & initialize(Framebuffer * framebuffers[2]);
	private:
		GUI(Framebuffer * framebuffers[2]);

		void swapBuffers();
		Framebuffer & frontbuffer() { return *framebuffers[activeFramebuffer]; }
		Framebuffer & backbuffer() { return *framebuffers[activeFramebuffer ^ 1]; }

		Framebuffer ** framebuffers;
		unsigned int activeFramebuffer;

		bool initialized;
};

#endif
