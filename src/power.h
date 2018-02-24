// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#ifndef POWER_H
#define POWER_H

class Power final
{
	public:
		static Power & get();

		void enableOverdrive();
	private:
		static void initialize();
		static bool initialized;
};

#endif
