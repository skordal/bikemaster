# Bikemaster

Bikemaster is a bicycle computer, showing speed, distance and interesting statistics
during and after a bike trip. It runs on the STM32F746NG Discovery board, with a
sensor made with a reed switch and a magnet attached to one of the wheel spokes of
the bicycle.

## How to Build

At the moment, no makefiles are provided. Import the source files into your favourite
IDE and hit the "compile" button. The application has been developed using Rowley's
CrossStudio, but will probably work with other IDEs.

## Configuring

Go to the `sensor.cpp` file and change the `WHEEL_DIAMETER` constant to the diameter
of the wheel in meters.

## Hardware use

The application uses many of the hardware peripherals available on the STM32F7 chip.
The following list lists the resources in use, and what they are used for:

* CRC: used to create and verify checksums for measurements stored in flash.
* DMA2D: used to clear framebuffers between frames
* FLASH: used to store trip data
* FMC: the flexible memory controller, used to configure the SDRAM.
* EXTI: external interrupts for GPIOs and software interrupts
  * EXTI0: GUI update software interupt
  * EXTI2: wheel sensor
  * EXTI11: user button, used as additional sensor input
  * EXTI13: touchscreen interrupt input
* GPIO: used for handling button presses, controlling the user LED and configuring
  the multitude of multiplexed I/O pins used by the other peripherals.
* I2C3: used to communicate with the touchscreen controller
* LTDC: LCD display controller
* TIM2: timer used for GUI animation timings
* TIM3: timer used for wheel sensor timeouts
* TIM4: timer used for wheel sensor timing
* TIM5: timer used for trip event timestamping
* TIM10: used as blocking delay timer during initialization

