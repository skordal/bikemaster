// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include "button.h"
#include "utils.h"

Button::Button(const Point & origin, const Image & image, void (*callback)(void *), void * data)
	: origin(origin), image(image), callback(callback), data(data)
{

}

void Button::render(Framebuffer & fb)
{
	const float h = 0.707106781f;
	const Point imageOffset(origin.getX() - static_cast<unsigned int>(h * RADIUS),
			origin.getY() - static_cast<unsigned int>(h * RADIUS));

	Utils::drawCircle(fb, origin, RADIUS, OUTLINE_COLOR);
	FramebufferViewport viewport(fb, imageOffset, RADIUS * 2.0f * h, RADIUS * 2.0f * h);
	image.render(viewport);
}
