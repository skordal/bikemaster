// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

#include <cstdint>
#include "point.h"

class TouchscreenEvent final : public Point
{
};

class TouchscreenListener
{
	public:
		virtual void handleTouchscreenEvent(const TouchscreenEvent & event) = 0;
};

extern "C" void EXTI15_10_IRQHandler();
extern "C" void I2C3_EV_IRQHandler();

class Touchscreen final
{
	public:
		static Touchscreen & get();
		static void initialize();

		void setListener(TouchscreenListener * listener) { this->listener = listener; }
	private:
		void initializeGPIO();
		void initializeI2C();
		void configureTouch();

		void interrupt();

		void readRegister(uint8_t reg, void (*callback)(uint8_t data));
		void writeRegister(uint8_t reg, uint8_t value, void (*callback)());
		void startTransfer();
		void finishTransfer();

		struct I2CTransfer
		{
			enum class Type
			{
				READ, WRITE
			};

			void setRegister(uint8_t reg) { buffer[0] = reg; }
			uint8_t getRegister() const { return buffer[0]; }
			void setData(uint8_t data) { buffer[1] = data; }
			uint8_t getData() const { return buffer[1]; }

			Type type;
			uint8_t buffer[2]; // 0 = register address, 1 = data buffer
			union {
				void (*readCallback)(uint8_t data);
				void (*writeCallback)();
			};
		};

		TouchscreenListener * listener = nullptr;

        I2CTransfer currentTransfer;
		TouchscreenEvent currentEvent;
		volatile bool transferActive = false;

		static const uint8_t TOUCHSCREEN_ADDRESS = 0x70;
		static const uint8_t REGADDR_STATUS = 0x02;
		static const uint8_t REGADDR_TOUCHXH = 0x03;
		static const uint8_t REGADDR_TOUCHXL = 0x04;
		static const uint8_t REGADDR_TOUCHYH = 0x05;
		static const uint8_t REGADDR_TOUCHYL = 0x06;
		static const uint8_t REGADDR_MODE = 0xa4;

	friend void EXTI15_10_IRQHandler();
	friend void I2C3_EV_IRQHandler();
};

#endif
