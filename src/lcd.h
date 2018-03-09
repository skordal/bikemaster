// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef LCD_H
#define LCD_H

#include "config.h"
#include "color.h"
#include "framebuffer.h"

extern "C" void LTDC_IRQHandler();

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

class LCDUpdateListener
{
	public:
		virtual void onLCDUpdated() = 0;
};

class LCD final
{
	public:
		static LCD & get();

		LCDLayer & getLayer(unsigned int layer) { return layers[layer]; }
		void enable();
		void disable();

		void setBackgroundColor(const Color & bg);

		void setListener(LCDUpdateListener * listener) { this->listener = listener; }
	private:
		LCD();
		void initialize();
        void setupGPIOs();

		// Reload shadow registers:
		void reload();

		bool initialized = false;
		LCDLayer layers[2]{0, 1};
		LCDUpdateListener * listener = nullptr;

	friend class LCDLayer;
	friend class LCDUpdateListener;
	friend void LTDC_IRQHandler();
};

#endif
