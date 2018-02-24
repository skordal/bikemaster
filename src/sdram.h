// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef SDRAM_H
#define SDRAM_H

class SDRAM
{
	public:
		static void initialize();
	private:
		static void setupGPIOs();
};

#endif
