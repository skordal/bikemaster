// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef BUTTON_H
#define BUTTON_H

#include "framebuffer.h"
#include "image.h"
#include "point.h"
#include "touchscreen.h"

class Button final : public TouchscreenListener
{
	public:
		static constexpr const float RADIUS = 30;

		Button(const Image & image, void (*callback)(void *), void * data = nullptr)
			: Button(Point(0, 0), image, callback, data) {}
		Button(const Point & origin, const Image & image, void (*callback)(void *), void * data = nullptr);

		void setOrigin(const Point & origin) { this->origin = origin; }
		const Point & getOrigin() const { return origin; }

		void render(Framebuffer & fb);
		void handleTouchscreenEvent(const TouchscreenEvent & event) override;

		void trigger() const { if(callback != nullptr) callback(data); }
	private:
		Point origin;
		const Image & image;
		void (*callback)(void * data);
		void * data;

		const Color OUTLINE_COLOR = Color(200, 200, 200);
};

#endif
