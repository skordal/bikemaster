// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <cmath>
#include <cross_studio_io.h>

#include "config.h"
#include "font.h"
#include "images.h"
#include "mainscreen.h"
#include "sensor.h"
#include "strings.h"
#include "utils.h"

using Utils::abs;

const Color MainScreen::SPEEDOMETER_COLOR(255, 255, 255);
const Color MainScreen::TICKMARK_COLOR(180, 180, 180);
const Color MainScreen::NEEDLE_COLOR(255, 0, 0);
const Color MainScreen::BUTTON_OUTLINE_COLOR(180, 180, 200);

void MainScreen::animate()
{
	speed = Sensor::get().getSpeed() * 3.6f;
	distance = Sensor::get().getDistance();

	if(needleValue < speed - NEEDLE_MARGIN)
	{
		if(needleSpeed > 0.0f && needleSpeed < NEEDLE_MAX_SPEED)
			needleSpeed += NEEDLE_ACCELERATION;
		else
			needleSpeed = NEEDLE_ACCELERATION;

		if(needleValue + needleSpeed > speed)
			needleValue = speed;
		else
			needleValue += needleSpeed;
	} else if(needleValue > speed + NEEDLE_MARGIN)
	{
		if(needleSpeed < 0.0f && needleSpeed > -NEEDLE_MAX_SPEED)
			needleSpeed -= NEEDLE_ACCELERATION;
		else
			needleSpeed = NEEDLE_ACCELERATION;

		if(needleValue - needleSpeed < speed || needleValue - needleSpeed <= 0.0f)
			needleValue = speed;
		else
			needleValue -= needleSpeed;
	} else
		needleSpeed = 0.0f;
}

void MainScreen::render(Framebuffer & fb)
{
	const unsigned int radiusOuter = (fb.getWidth() - 1) / 2;
	const unsigned int radiusInner = radiusOuter - SPEEDOMETER_WIDTH;

	// Draw outer semicircle:
	Utils::drawCircle(fb, Point((fb.getWidth() - 1) / 2, fb.getHeight() - 1),
		radiusOuter, SPEEDOMETER_COLOR, Utils::CircleDrawingMode::UPPER_SEMICIRCLE);

	// Draw inner semicircle:
	Utils::drawCircle(fb, Point((fb.getWidth() - 1) / 2, fb.getHeight() - 1),
		radiusInner, SPEEDOMETER_COLOR, Utils::CircleDrawingMode::UPPER_SEMICIRCLE);

	drawTickmarks(fb, float(radiusInner), float(radiusOuter));
	drawNeedle(fb, float(radiusInner), float(radiusOuter));
	drawText(fb);
	drawButtons(fb);
}

void MainScreen::drawTickmarks(Framebuffer & fb, float radiusInner, float radiusOuter)
{
	const unsigned int centerX = (fb.getWidth() - 1) / 2;
	const unsigned int centerY = fb.getHeight() - 1;

	const float majorInterval = M_PI / (CONFIG_GUI_MAXSPEED / 10.0f);
	for(float angle = 0.0f; angle < M_PI; angle += majorInterval)
	{
		float cosAngle = cosf(angle), sinAngle = sinf(angle);

		float startX = centerX + cosAngle * radiusInner;
		float endX = centerX + cosAngle * radiusOuter;

		float startY = centerY - sinAngle * radiusInner;
		float endY = centerY - sinAngle * radiusOuter;

		Utils::drawLine(fb, Point(startX, startY), Point(endX, endY), TICKMARK_COLOR);
	}

	Utils::drawLine(fb, Point(centerX - radiusOuter, centerY), Point(centerX - radiusInner, centerY),
		TICKMARK_COLOR);
}

void MainScreen::drawNeedle(Framebuffer & fb, float radiusInner, float radiusOuter)
{
	const unsigned int centerX = (fb.getWidth() - 1) / 2;
	const unsigned int centerY = fb.getHeight() - 1;

	if(needleValue <= NEEDLE_MARGIN)
		needleValue = 0.0f;
	else if(needleValue >= CONFIG_GUI_MAXSPEED)
		needleValue = CONFIG_GUI_MAXSPEED;

	const float angle = M_PI - (M_PI / CONFIG_GUI_MAXSPEED) * needleValue;

	float cosAngle = cosf(angle), sinAngle = sinf(angle);
	float startX = centerX + cosAngle * radiusInner;
	float endX = centerX + cosAngle * radiusOuter;

	float startY = centerY - sinAngle * radiusInner;
	float endY = centerY - sinAngle * radiusOuter;

	Utils::drawLine(fb, Point(startX, startY), Point(endX, endY), NEEDLE_COLOR);
}

void MainScreen::drawText(Framebuffer & fb)
{
	const unsigned int centerX = (fb.getWidth() - 1) / 2;
    Font & font = Font::getDefault();

	// Text Y placements:
	const unsigned int speedHeaderY = fb.getHeight() - (font.getHeight() + 2) * 6;
	const unsigned int speedNumberY = fb.getHeight() - (font.getHeight() + 2) * 5;
	const unsigned int distanceHeaderY = fb.getHeight() - (font.getHeight() + 2) * 3;
	const unsigned int distanceNumberY = fb.getHeight() - (font.getHeight() + 2) * 2;

	// Render the speed header:
	{
		const wchar_t * headerText = Strings::get(Strings::ID::SPEED, CONFIG_GUI_LANGUAGE);
		const unsigned int x = centerX - font.getWidth(headerText) / 2;
		font.render(fb, Point(x, speedHeaderY), headerText);
	}

	// Render the speed itself:
	{
		wchar_t textBuffer[10];
		Strings::formatSpeedString(speed, textBuffer, CONFIG_GUI_LANGUAGE);
		const unsigned int x = centerX - font.getWidth(textBuffer) / 2;
		font.render(fb, Point(x, speedNumberY), textBuffer);
	}

	// Render the distance header:
	{
		const wchar_t * headerText = Strings::get(Strings::ID::DISTANCE, CONFIG_GUI_LANGUAGE);
		const unsigned int x = centerX - font.getWidth(headerText) / 2;
		font.render(fb, Point(x, distanceHeaderY), headerText);
	}

	// Render the distance itself:
	{
		wchar_t textBuffer[10];
		Strings::formatDistanceString(Sensor::get().getDistance(), textBuffer, CONFIG_GUI_LANGUAGE);
		const unsigned int x = centerX - font.getWidth(textBuffer) / 2;
		font.render(fb, Point(x, distanceNumberY), textBuffer);
	}
}

void MainScreen::drawButtons(Framebuffer & fb)
{
	const float h = 0.707106781f; // sin(45) = cos(45) = h

	const Point statisticsButtonOrigin(BUTTON_RADIUS + BUTTON_MARGIN, BUTTON_RADIUS + BUTTON_MARGIN);
	const Point utilityButtonOrigin(fb.getWidth() - BUTTON_RADIUS - BUTTON_MARGIN,
		BUTTON_RADIUS + BUTTON_MARGIN);

	// Draw the button outlines:
	Utils::drawCircle(fb, statisticsButtonOrigin, BUTTON_RADIUS, BUTTON_OUTLINE_COLOR);
    Utils::drawCircle(fb, utilityButtonOrigin, BUTTON_RADIUS, BUTTON_OUTLINE_COLOR);

	const Point imageOffsets[2]{
		{statisticsButtonOrigin.getX() - static_cast<unsigned int>(h * BUTTON_RADIUS),
			statisticsButtonOrigin.getY() - static_cast<unsigned int>(h * BUTTON_RADIUS)},
		{utilityButtonOrigin.getX() - static_cast<unsigned int>(h * BUTTON_RADIUS),
			utilityButtonOrigin.getY() - static_cast<unsigned int>(h * BUTTON_RADIUS)}
	};

	// Draw the statistics button graphic:
	FramebufferViewport viewport(fb, imageOffsets[0], BUTTON_RADIUS * 2.0f * h, BUTTON_RADIUS * 2.0f * h);
	Images::Buttons::statisticsButton().render(viewport);

	// Draw the trip button graphic:
	viewport.setOffset(imageOffsets[1]);
	Images::Buttons::tripButton().render(viewport);
}
