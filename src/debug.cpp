// Bikemaster - A bike statistics solution
// (c) Kristian Klomsten Skordal 2018 <kristian.skordal@wafflemail.net>
// Report bugs and issues on <https://github.com/skordal/bikemaster/issues>

#include <cross_studio_io.h>

#include "debug.h"

Debug Debug::debugStream;

Debug & operator<<(Debug & stream, const char * string)
{
	debug_printf(string);
	return stream;
}

Debug & operator<<(Debug & stream, unsigned int i)
{
	debug_printf("0x%.08x", i);
	return stream;
}

Debug & operator<<(Debug & stream, float f)
{
	debug_printf("%f", f);
	return stream;
}
