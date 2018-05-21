// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include "images.h"
#include "utils.h"

namespace Images
{
	class BackButtonImage final : public Image
	{
		public:
			void render(Framebuffer & fb) const override
			{
				const Point arrowPoint(MARGIN, fb.getHeight() / 2);
				const Point arrowTop = arrowPoint.offset(ARROWHEAD_WIDTH, -(ARROWHEAD_HEIGHT / 2));
				const Point arrowBottom = arrowPoint.offset(ARROWHEAD_WIDTH, ARROWHEAD_HEIGHT / 2);
				const Point arrowShaftTop = arrowTop.offset(0, ARROWHEAD_HEIGHT / 4);
				const Point arrowShaftBottom = arrowBottom.offset(0, -(ARROWHEAD_HEIGHT / 4));

				Utils::drawLine(fb, arrowPoint, arrowTop, ARROW_COLOR);
                Utils::drawLine(fb, arrowPoint, arrowBottom, ARROW_COLOR);
				Utils::drawLine(fb, arrowTop, arrowShaftTop, ARROW_COLOR);
				Utils::drawLine(fb, arrowBottom, arrowShaftBottom, ARROW_COLOR);
				Utils::drawLine(fb, arrowShaftTop, Point(fb.getWidth() - MARGIN, arrowShaftTop.getY()), ARROW_COLOR);
				Utils::drawLine(fb, arrowShaftBottom, Point(fb.getWidth() - MARGIN, arrowShaftBottom.getY()), ARROW_COLOR);
				Utils::drawLine(fb,
					Point(fb.getWidth() - MARGIN, arrowShaftTop.getY()),
					Point(fb.getWidth() - MARGIN, arrowShaftBottom.getY()),
					ARROW_COLOR);
			}
		private:
			const unsigned int MARGIN = 4;
			const unsigned int ARROWHEAD_WIDTH = 20;
			const unsigned int ARROWHEAD_HEIGHT = 30;
            const Color ARROW_COLOR = Color(180, 180, 180);
	};

	const Image & Buttons::backButton()
	{
		static BackButtonImage image;
		return image;
	}

	class StatisticsButtonImage final : public Image
	{
		public:
			void render(Framebuffer & fb) const override
			{
				// Draw the coordinate system:
				Utils::drawLine(fb, Point(H_MARGIN, V_MARGIN),
					Point(H_MARGIN, fb.getHeight() - V_MARGIN),
					Color(180, 180, 180));
				Utils::drawLine(fb, Point(H_MARGIN, fb.getHeight() - V_MARGIN),
					Point(fb.getWidth() - H_MARGIN, fb.getHeight() - V_MARGIN),
					Color(180, 180, 180));

				// Draw some bars:
				const Color barColors[NUM_BARS]{
					{150, 40, 40},
					{220, 170, 40},
					{60, 50, 170},
					{40, 130, 40}
				};
				const unsigned int barWidth = (fb.getWidth() - 2 * H_MARGIN - 1) / NUM_BARS;
				const unsigned int barHeights[NUM_BARS] = {18, 13, 22, 16};
				for(unsigned int i = 0; i < NUM_BARS; ++i)
				{
					const Point startPos(H_MARGIN + barWidth * i + 1, fb.getHeight() - V_MARGIN - barHeights[i]);
					Utils::fillRectangle(fb, startPos, barWidth, barHeights[i], barColors[i]);
				}
			}
		private:
			const unsigned int H_MARGIN = 4;
			const unsigned int V_MARGIN = 8;
			const unsigned int NUM_BARS = 4;
	};

	const Image & Buttons::statisticsButton()
	{
		static StatisticsButtonImage image;
		return image;
	}

	class TripButtonImage final : public Image
	{
		public:
			void render(Framebuffer & fb) const override
			{
				// Draw the bike wheels:
				const Point wheels[2]{
					{ MARGIN, fb.getHeight() - MARGIN - WHEEL_RADIUS },
					{ fb.getWidth() - MARGIN, fb.getHeight() - MARGIN - WHEEL_RADIUS }
				};
				Utils::drawCircle(fb, wheels[0], WHEEL_RADIUS, bikeColor);
				Utils::drawCircle(fb, wheels[1], WHEEL_RADIUS, bikeColor);

				// Draw the bike frame:
				const Point frameStart(wheels[0].getX() + 6, wheels[0].getY() - 12);
                const Point frameEnd(wheels[1].getX(), wheels[1].getY() - 12);
				Utils::drawLine(fb, wheels[0], frameStart, bikeColor);
				Utils::drawLine(fb, wheels[1], frameEnd, bikeColor);
				Utils::drawLine(fb, frameStart, frameEnd, bikeColor);

				// Draw the handlebar
				Utils::drawLine(fb, frameEnd, frameEnd.offset(0, -6), bikeColor);
				Utils::drawLine(fb, frameEnd.offset(0, -6), frameEnd.offset(-6, -6), bikeColor);
			}

		private:
			const Color bikeColor = Color(180, 180, 180);

			const unsigned int WHEEL_RADIUS = 8;
			const unsigned int MARGIN = 8;
	};

	const Image & Buttons::tripButton()
	{
		static TripButtonImage image;
		return image;
	}
}
