// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef LCD_H
#define LCD_H

#include "config.h"
#include "framebuffer.h"

class LCDLayer final
{
	public:
		void enable(unsigned int x, unsigned int y, unsigned int w, unsigned int h, Framebuffer * fb);
		void disable();

		void setFramebuffer(Framebuffer * fb);
		Framebuffer * getFramebuffer() { return fb; }
		const Framebuffer * getFramebuffer() const { return fb; }
	private:
		LCDLayer(unsigned int index) : index(index) {}

		unsigned int index;
		Framebuffer * fb;
	friend class LCD;
};

class LCD final
{
	public:
		static LCD & get();

		LCDLayer & getLayer(unsigned int layer) { return layers[layer]; }
		void enable();
		void disable();
	private:
		LCD();
		void initialize();
        void setupGPIOs();

		// Reload shadow registers:
		void reload();

		bool initialized = false;
		LCDLayer layers[2]{0, 1};
	friend class LCDLayer;
};

#endif
