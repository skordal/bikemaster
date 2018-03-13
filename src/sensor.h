// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef SENSOR_H
#define SENSOR_H

extern "C" void TIM3_IRQHandler();
extern "C" void EXTI15_10_IRQHandler();

class SensorListener
{
	public:
		virtual void onSpeedUpdated(float newSpeed) = 0;
		virtual void onDistanceUpdated(float newDistance) = 0;
	private:
		SensorListener * next;

	friend class Sensor;
};

class Sensor final
{
	public:
		static Sensor & get();

		float getSpeed();
		float getDistance() const { return float(halfRevolutions) * WHEEL_CIRCUMFERENCE / 2.0f; }
	private:
		Sensor() : initialized(false) {}
		void initialize();

		void interrupt();

		// Current speed:
		mutable float speed = 0.0f;

		// Total number of half revolutions:
		unsigned long halfRevolutions = 0;

		// 10 Hz timer ticks:
		unsigned long prevTimerTicks = 0;
		unsigned long timerTicks = 0;

        bool initialized = false;

		// Wheel circumference in meters:
		static constexpr const float WHEEL_CIRCUMFERENCE = 2.4f;
		static constexpr const float MIN_SPEED = 0.3f;

	friend void TIM3_IRQHandler();
	friend void EXTI15_10_IRQHandler();
};

#endif
