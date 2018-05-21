// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef SCREEN_H
#define SCREEN_H

#include "button.h"
#include "framebuffer.h"
#include "touchscreen.h"

class Screen : public TouchscreenListener
{
	public:
		virtual void render(Framebuffer & fb) = 0;
		virtual void animate() {};

		virtual void handleTouchscreenEvent(const TouchscreenEvent & event);
		virtual Color getBackground() const { return Color::black(); }
	protected:
		void renderButtons(Framebuffer & fb) const;

		void addButton(unsigned int slot, Button * button);
		void removeButton(unsigned int slot) { buttonSlots[slot] = nullptr; }

		Point getButtonOrigin(unsigned int slot) const;

		static const unsigned int BUTTON_MARGIN = 20;   // Pixels on either side of the button row.
        static const unsigned int NUM_BUTTON_SLOTS = 6; // Number of buttons to support
	private:
		Button * buttonSlots[NUM_BUTTON_SLOTS];
};

#endif
