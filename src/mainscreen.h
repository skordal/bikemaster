// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "color.h"
#include "framebuffer.h"
#include "screen.h"

class MainScreen final : public Screen
{
	public:
		void animate() override;
		void render(Framebuffer & fb) override;
	private:
		void drawTickmarks(Framebuffer & fb, float radiusInner, float radiusOuter);
		void drawNeedle(Framebuffer & fb, float radiusInner, float radiusOuter);
		void drawText(Framebuffer & fb);

		float distance = 0.0f;
		float speed = 0.0f;

		float needleValue = 0.0f;
		float needleSpeed = 0.0f;

		static constexpr const float NEEDLE_ACCELERATION = 0.1f;
		static constexpr const float NEEDLE_MAX_SPEED = 1.0f;
		static constexpr const float NEEDLE_MARGIN = 0.25f;

		static const unsigned int SPEEDOMETER_WIDTH = 85;

		static const Color SPEEDOMETER_COLOR;
		static const Color TICKMARK_COLOR;
		static const Color NEEDLE_COLOR;
};

#endif
