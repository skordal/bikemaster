// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef SENSOR_H
#define SENSOR_H

#include <cmath>
#include "listener.h"

extern "C" void TIM3_IRQHandler();
extern "C" void TIM4_IRQHandler();
extern "C" void EXTI2_IRQHandler();
extern "C" void EXTI15_10_IRQHandler();

class SensorListener : public Listener
{
	public:
		virtual void handleSpeedChanged(float newSpeed) { (void) newSpeed; }
		virtual void handleWheelRevolution() {}
};

class Sensor final : public Listenable<SensorListener>
{
	public:
		static Sensor & get();

		float getSpeed() const { return speed; }
		float getWheelDiameter() const { return WHEEL_DIAMETER; }
	private:
		Sensor() : initialized(false) {}
		void initialize();

		void interrupt();
		void timerInterrupt() { speedTimerOverflow = true; }
		void timeout();

		float calculateSpeedReduction() const;
		void callListeners(float speed, bool revolution) const;

		// Current speed:
		volatile float speed = 0.0f;

		// The wheel speed timer has overflowed:
		volatile bool speedTimerOverflow = false;

		// Sensor initialized:
        bool initialized = false;

		// Wheel circumference in meters:
		static constexpr const float WHEEL_DIAMETER = 0.7f;	// m
		static constexpr const float MINIMUM_SPEED = 1.0f;	// m/s
		static constexpr const float MAXIMUM_SPEED = 13.9f;	// m/s
		static const unsigned int DEBOUNCE_COUNT = 250;

	friend void TIM3_IRQHandler();
	friend void TIM4_IRQHandler();
	friend void EXTI2_IRQHandler();
	friend void EXTI15_10_IRQHandler();
};

#endif
