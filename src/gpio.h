// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef GPIO_H
#define GPIO_H

#include <cstdint>

namespace GPIO
{
	enum class Port : uint8_t
	{
		A, B, C, D, E, F, G, H, I, J, K
	};

	enum class Mode : uint8_t
	{
		INPUT, OUTPUT, ALTERNATE, ANALOG
	};

	enum class OutputType : uint8_t
	{
		PUSH_PULL, OPEN_DRAIN
	};

	enum class OutputSpeed : uint8_t
	{
		LOW_SPEED, MEDIUM_SPEED, HIGH_SPEED, VERY_HIGH_SPEED
	};

	enum class PullMode : uint8_t
	{
		NONE, PULL_UP, PULL_DOWN
	};

	class Controller final
	{
		private:
			static Controller & get(Port port);

            Controller(Port port);

			void setMode(uint8_t pin, Mode mode);
			void setOutputType(uint8_t pin, OutputType type);
			void setOutputSpeed(uint8_t pin, OutputSpeed speed);
			void setPullMode(uint8_t pin, PullMode pull);
			void setAlternate(uint8_t pin, uint8_t alternate);

			void set(uint8_t pin, uint8_t value = 1u);
			void clear(uint8_t pin) { set(pin, 0); }
			bool read(uint8_t pin);

			Port port;
		friend class Pin;
	};

    class Pin final
	{
		public:
			Pin(uint8_t pin, Port port) : pin(pin), port(port) {}

			void setMode(Mode mode) { controller().setMode(pin, mode); }
			void setType(OutputType type) { controller().setOutputType(pin, type); }
			void setSpeed(OutputSpeed speed) { controller().setOutputSpeed(pin, speed); }
			void setAlternate(uint8_t alternate) { controller().setAlternate(pin, alternate); }
			void setPullMode(PullMode pull) { controller().setPullMode(pin, pull); }

			void set() { controller().set(pin); }
			void clear() { controller().clear(pin); }

			bool read() { return controller().read(pin); }
		private:
			Controller & controller() const { return Controller::get(port); }

			uint8_t pin;
			Port port;
	};
}

#endif
