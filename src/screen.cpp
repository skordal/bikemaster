// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <cmath>

#include "debug.h"
#include "screen.h"

void Screen::handleTouchscreenEvent(const TouchscreenEvent & event)
{
	for(unsigned int i = 0; i < NUM_BUTTON_SLOTS; ++i)
	{
		if(buttonSlots[i] == nullptr)
			continue;
		if(event.within(getButtonOrigin(i).offset(-Button::RADIUS, -Button::RADIUS), Button::RADIUS * 2, Button::RADIUS * 2))
			buttonSlots[i]->trigger();
	}
}

void Screen::renderButtons(Framebuffer & fb) const
{
	for(Button * button : buttonSlots)
		if(button != nullptr)
			button->render(fb);
}

void Screen::addButton(unsigned int slot, Button * button)
{
	buttonSlots[slot] = button;
	button->setOrigin(getButtonOrigin(slot));
}

Point Screen::getButtonOrigin(unsigned int slot) const
{
	const int buttonDiameter = 2 * static_cast<int>(Button::RADIUS);
	const unsigned int interButtonSpace = (480 - (2 * BUTTON_MARGIN) - (NUM_BUTTON_SLOTS * buttonDiameter))
		/ (NUM_BUTTON_SLOTS - 1);

	return Point(BUTTON_MARGIN + Button::RADIUS + slot * buttonDiameter + slot * interButtonSpace,
		BUTTON_MARGIN + Button::RADIUS);
}
